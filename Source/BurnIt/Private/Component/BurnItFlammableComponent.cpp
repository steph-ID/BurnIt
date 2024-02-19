// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BurnItFlammableComponent.h"

#include "Actor/BurnItFlammableActor.h"
#include "Character/BurnItCharacter.h"
#include "Core/BurnItGameStateBase.h"
#include "Core/BurnItPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBurnItFlammableComponent::UBurnItFlammableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set player specific variables
	if (ABurnItPlayerState* PS = Cast<ABurnItPlayerState>(GetOwner()))
	{
		PlayerState = PS;
		bIsPlayer = true;
		FlammableObject.CurrentTemperature = 37.f;
	}

	// Initialize Health to be MaxHealth
	SetHealth(GetMaxHealth());

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
	// Set the health, clamped so it doesn't go under 0 or above the max health
	FlammableObject.Health = FMath::Clamp(NewHealth, 0, GetMaxHealth());
}

void UBurnItFlammableComponent::AdjustHealth(float HealthToAdd)
{
	// Set new health value
	SetHealth(GetHealth() + HealthToAdd);

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

void UBurnItFlammableComponent::UpdateHeatVisualizationMaterial()
{
	// Find the % the current temperature is between base temperature and ignition temperature
	const float HeatedMaterialVisibilityPercent = FMath::GetRangePct(GetBaseTemperature(), GetIgnitionTemperature(), GetCurrentTemperature());
	
	// Map the visibility change (0-1) to happen slowly at first then quickly and call SetHeatedMaterialVisibility blueprint function
	GetFlammableActor()->SetHeatedMaterialVisibility(FMath::InterpEaseIn(0.f, 1.f, HeatedMaterialVisibilityPercent, 2.f));
}

void UBurnItFlammableComponent::AdjustTemperature(float TempToAdd, bool bIsTouchedByFlames, AActor* Instigator)
{
	// TODO: Might be bugged since it relies on garbage collection timer
	HeatSources.Shrink();
	CurrentHeatSources = HeatSources.Num();
	
	// If the object is already on fire and at the burn temperature, do not continue to adjust heat
	if (bIsOnFire && GetCurrentTemperature() >= GetBurnTemperature())
	{
		return;
	}
	
	// Add the instigating actor to a list of unique actors affecting this object so we can apply diminishing returns later
	if (CurrentHeatSources < MaxHeatSourcesUntilDiminishedReturns && Instigator != nullptr)
	{
		HeatSources.AddUnique(Instigator);
		CurrentHeatSources = HeatSources.Num();
		//HeatSources.RemoveAll(nullptr);
	}
	
	// Adjust the CurrentTemperature if CurrentHeatSources > 0 (no division by 0)
	if ((bIsTouchedByFlames || bIsOnFire) && CurrentHeatSources > 0.f)
	{
		AdjustCurrentTemperature(TempToAdd*(HeatTransferenceRate*2)/(CurrentHeatSources*0.66f));
	}
	else
	{
		AdjustCurrentTemperature(TempToAdd*HeatTransferenceRate);
	}
	
	// Change opacity of heat visualization material
	UpdateHeatVisualizationMaterial();

	// Start time-to-cool timer
	GetWorld()->GetTimerManager().SetTimer(CoolingTimerHandle, CoolingTimerDelegate, CoolingTickRate, false, GetTimeUntilCooling());

	// Tell object to catch fire or melt when the ignition or autoignition temperature is met 
	if (!bIsOnFire && ((bIsTouchedByFlames && (GetCurrentTemperature() >= GetIgnitionTemperature())) || GetCurrentTemperature() >= GetAutoIgnitionTemperature()))
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

	// Stop the object from cooling while on fire
	GetWorld()->GetTimerManager().ClearTimer(CoolingTimerHandle);

	// Start the burn damage DoT
	GetWorld()->GetTimerManager().SetTimer(BurnDamageTimerHandle, BurnDamageTimerDelegate, 1.f, true, 0.f);
}

void UBurnItFlammableComponent::ExtinguishFire()
{
	bIsOnFire = false;

	// Tell actor to turn off flame FX
	GetFlammableActor()->Extinguish();

	// Stop the burn damage DoT
	GetWorld()->GetTimerManager().ClearTimer(BurnDamageTimerHandle);

	// If the object isn't destroyed/dead, begin cooling to base temperature
	if(GetHealth() > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(CoolingTimerHandle, CoolingTimerDelegate, CoolingTickRate, true, GetTimeUntilCooling());
	}
}

void UBurnItFlammableComponent::Melt() const
{
	GetFlammableActor()->Melt();
}

void UBurnItFlammableComponent::Burn()
{
	const float BurnDamage = -GetBurnTemperature()/1000.f;
	AdjustHealth(BurnDamage);
	GetFlammableActor()->Propagate();
}

void UBurnItFlammableComponent::Cool()
{
	
	// Only run if not on fire and the current temp is not the base temp
	if (!bIsOnFire)
	{
		// Remove all heat source tracking
		HeatSources.Empty();
		CurrentHeatSources = HeatSources.Num();
		
		if(GetCurrentTemperature() != GetBaseTemperature())
		{
			const float TempChange = (GetBaseTemperature() - GetCurrentTemperature())*CoolingRate;
			AdjustCurrentTemperature(TempChange);

			// Change opacity of heat visualization material
			UpdateHeatVisualizationMaterial();
		
			// When close enough to the base temperature, set to base temp. This keeps the object from staying in the cooling state for an unnecessary amount of time
			if (FMath::IsNearlyEqual(GetCurrentTemperature(), GetBaseTemperature(), 0.09f))
			{
				SetCurrentTemperature(GetBaseTemperature());
				GetWorld()->GetTimerManager().ClearTimer(CoolingTimerHandle);
			}
			else // Continue to cool if not near the base temperature
			{
				GetWorld()->GetTimerManager().SetTimer(CoolingTimerHandle, CoolingTimerDelegate, CoolingTickRate, false, CoolingTickRate);
			}
		}
	}
	//ABurnItLevelDataManager* LevelDataManager =
}

void UBurnItFlammableComponent::SendPoints()
{
	// If the current game state is not Playing, do not continue on to award points
	ABurnItGameStateBase* GS = Cast<ABurnItGameStateBase>(UGameplayStatics::GetGameState(this));
	if (GS->GetCurrentGameState() != EGameState::Playing)
	{
		return;
	}

	// Award points to the player
	const ABurnItPlayerController* PC = Cast<ABurnItPlayerController>(GetWorld()->GetFirstPlayerController());
	ABurnItPlayerState* PS = PC->GetPlayerState<ABurnItPlayerState>();
	PS->SetPlayerScore(FlammableObject.PointValue);
}

void UBurnItFlammableComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UBurnItFlammableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

