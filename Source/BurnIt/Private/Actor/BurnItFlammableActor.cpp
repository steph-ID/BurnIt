// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BurnItFlammableActor.h"

// Sets default values
ABurnItFlammableActor::ABurnItFlammableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlammableComponent = CreateDefaultSubobject<UBurnItFlammableComponent>(TEXT("FlammableComponent"));

	//StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMeshComponent->SetupAttachment(RootComponent);
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

void ABurnItFlammableActor::Propagate_Implementation()
{
}

void ABurnItFlammableActor::Extinguish_Implementation()
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

