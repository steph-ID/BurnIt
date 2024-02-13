// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BurnItFlammableComponent.h"

#include "Actor/BurnItFlammableActor.h"
#include "Character/BurnItCharacter.h"
#include "Core/BurnItPlayerController.h"

// Sets default values for this component's properties
UBurnItFlammableComponent::UBurnItFlammableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	if (ABurnItPlayerState* PS = Cast<ABurnItPlayerState>(GetOwner()))
	{
		PlayerState = PS;
		bIsPlayer = true;
		FlammableObject.CurrentTemperature = 37.f;
	}

	// Initialize Health to be MaxHealth
	FlammableObject.Health = FlammableObject.MaxHealth;

	// Bind Burn DoT function
	BurnDamageTimerDelegate.BindUFunction(this, FName("Burn"));

	// Bind cooling timer function
	CoolingTimerDelegate.BindUFunction(this, FName("Cool"));
}

ABurnItCharacter* UBurnItFlammableComponent::GetBurnItCharacter() const
{
	ABurnItCharacter* Character = Cast<ABurnItCharacter>(PlayerState->GetPlayerController()->GetCharacter());
	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UBurnItFlammableComponent: Player character is nullptr."));
	}
	return Character;
}

ABurnItFlammableActor* UBurnItFlammableComponent::GetFlammableActor() const
{
	return Cast<ABurnItFlammableActor>(GetOwner());
}

void UBurnItFlammableComponent::SetHealth(float NewHealth)
{
	// Set the health
	FlammableObject.Health += NewHealth;

	// Clamp health so it doesn't go under 0 or above the max health
	FlammableObject.Health = FMath::Clamp(FlammableObject.Health, 0, FlammableObject.MaxHealth);
}

void UBurnItFlammableComponent::AdjustHealth(float HealthToAdd)
{
	// Set new health value
	SetHealth(HealthToAdd);

	// Check for death of player or object and process if dead
	if (GetHealth() == 0)
	{
		if (bIsPlayer)
		{
			ProcessPlayerDeath();
		}
		else
		{
			ProcessObjectDeath();
		}
	}

	// Update the HUD if health adjustment was to the player
	if(bIsPlayer)
	{
		OnHealthUpdated.Broadcast(GetHealth(), GetMaxHealth());
	}
}

void UBurnItFlammableComponent::ProcessObjectDeath()
{
	// Stop the object from burning
	ExtinguishFire();
	
	// Choose if to drop ash or turn into an ash "statue"
	if(FMath::RandRange(0.f, 1.f) > ChanceToTurnToAsh)
	{
		GetFlammableActor()->DropAsh();
	}
	else
	{
		GetFlammableActor()->TurnToAsh();
	}
	
	// Send points if object is not the player
	if(!bIsPlayer) SendPoints();
}

void UBurnItFlammableComponent::ProcessPlayerDeath()
{
	// Delay flames from extinguishing immediately
	// Activate death function on character
}

void UBurnItFlammableComponent::AdjustTemperature(float TempToAdd)
{
	FlammableObject.CurrentTemperature += TempToAdd/100.f;
	
	if (FlammableObject.CurrentTemperature >= FlammableObject.IgnitionTemperature)
	{
		if (FlammableObject.WillBurn)
		{
			CatchFire();
		}
		if (FlammableObject.WillMelt)
		{
			Melt();
		}
	}
}

void UBurnItFlammableComponent::CatchFire()
{
	bIsOnFire = true;

	// Tell actor to start flame FX
	GetFlammableActor()->Ignite();

	// Start the burn damage DoT
	GetWorld()->GetTimerManager().SetTimer(BurnDamageTimerHandle, BurnDamageTimerDelegate, 1, true, 0.f);
}

void UBurnItFlammableComponent::ExtinguishFire()
{
	bIsOnFire = false;

	// Tell actor to turn off flame FX
	GetFlammableActor()->Extinguish();

	// Stop the burn damage DoT
	GetWorld()->GetTimerManager().ClearTimer(BurnDamageTimerHandle);

	// If the object isn't destroyed/dead, being cooling to base temperature
	if(GetHealth() > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(CoolingTimerHandle, CoolingTimerDelegate, CoolingTickRate, true, CoolingDelay);
	}
}

void UBurnItFlammableComponent::Melt() const
{
	GetFlammableActor()->Melt();
}

void UBurnItFlammableComponent::Burn()
{
	const float BurnDamage = -GetBurnTemperature()/100.f;
	AdjustHealth(BurnDamage);
}

void UBurnItFlammableComponent::Cool()
{
	if (GetCurrentTemperature() != GetBaseTemperature())
	{
		const float TempChange = (GetBaseTemperature()-GetCurrentTemperature())/12.f;
		AdjustTemperature(TempChange);
		
		if (GetCurrentTemperature() <= GetBaseTemperature())
		{
			SetCurrentTemperature(GetBaseTemperature());
			GetWorld()->GetTimerManager().ClearTimer(CoolingTimerHandle);
		}
	}
	//ABurnItLevelDataManager* LevelDataManager =
}

void UBurnItFlammableComponent::SendPoints()
{
	const ABurnItPlayerController* PC = Cast<ABurnItPlayerController>(GetWorld()->GetFirstPlayerController());
	ABurnItPlayerState* PS = PC->GetPlayerState<ABurnItPlayerState>();
	PS->SetPlayerScore(FlammableObject.PointValue);
}

// Called when the game starts
void UBurnItFlammableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBurnItFlammableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

