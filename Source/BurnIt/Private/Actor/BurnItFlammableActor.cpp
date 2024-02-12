// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BurnItFlammableActor.h"

#include "Character/BurnItCharacter.h"

// Sets default values
ABurnItFlammableActor::ABurnItFlammableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlammableComponent = CreateDefaultSubobject<UBurnItFlammableComponent>(TEXT("FlammableComponent"));

	//StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMeshComponent->SetupAttachment(RootComponent);
	
	BurnDamageTimerDelegate.BindUFunction(this, FName("Burn"));
}

void ABurnItFlammableActor::StartBurning()
{
	bIsOnFire = true;
	Burn();
}

void ABurnItFlammableActor::StopBurning()
{
	bIsOnFire = false;
	GetWorldTimerManager().ClearTimer(BurnDamageTimerHandle);
	if(FlammableComponent->GetHealth() == 0)
	{
		if(FMath::RandRange(0.f, 1.f) > ChanceToTurnToAsh)
		{
			DropAsh();
		}
		else
		{
			TurnToAsh();
		}
	}
}

void ABurnItFlammableActor::Burn()
{
	const float BurnDamage = GetBurnTemperature()/100.f;
	FlammableComponent->AdjustHealth(-BurnDamage);
	GetWorldTimerManager().SetTimer(BurnDamageTimerHandle, BurnDamageTimerDelegate, 1, true, -1);
}

// Called when the game starts or when spawned
void ABurnItFlammableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABurnItFlammableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABurnItFlammableActor::Ignite_Implementation()
{
}

void ABurnItFlammableActor::TurnToAsh_Implementation()
{
}

void ABurnItFlammableActor::DropAsh_Implementation()
{
}

void ABurnItFlammableActor::Melt_Implementation()
{
}

