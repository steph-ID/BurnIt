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
		IsPlayer = true;
		FlammableObject.Temperature = 37.f;
	}

	FlammableObject.Health = FlammableObject.MaxHealth;
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

void UBurnItFlammableComponent::AdjustHealth(float HealthToAdd)
{
	FlammableObject.Health += HealthToAdd;
	FMath::Clamp(FlammableObject.Health, 0, FlammableObject.MaxHealth);
	if (FlammableObject.Health == 0)
	{
		if (IsPlayer)
		{
			ProcessPlayerDeath();
		}
		else
		{
			ProcessObjectDeath();
		}
	}
	if(IsPlayer)
	{
		OnHealthUpdated.Broadcast(FlammableObject.Health, FlammableObject.MaxHealth);
	}
}

void UBurnItFlammableComponent::ProcessObjectDeath()
{
	ABurnItFlammableActor* FlammableActor = Cast<ABurnItFlammableActor>(GetOwner());
	FlammableActor->StopBurning();
	SendPoints();
}

void UBurnItFlammableComponent::ProcessPlayerDeath()
{
}

void UBurnItFlammableComponent::AdjustTemperature(float TempToAdd)
{
	FlammableObject.Temperature += TempToAdd/100.f;
	
	if (FlammableObject.Temperature >= FlammableObject.IgnitionTemperature)
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

void UBurnItFlammableComponent::CatchFire() const
{
	ABurnItFlammableActor* FlammableActor = Cast<ABurnItFlammableActor>(GetOwner());
	FlammableActor->Ignite();
}

void UBurnItFlammableComponent::Melt() const
{
	ABurnItFlammableActor* FlammableActor = Cast<ABurnItFlammableActor>(GetOwner());
	FlammableActor->Melt();
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

