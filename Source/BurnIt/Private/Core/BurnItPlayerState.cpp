// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BurnItPlayerState.h"

#include "Component/BurnItFlammableComponent.h"

ABurnItPlayerState::ABurnItPlayerState()
{
	FlammableComponent = CreateDefaultSubobject<UBurnItFlammableComponent>(TEXT("FlammableComponent"));
}

void ABurnItPlayerState::SetPlayerName(const FString& S)
{
	Super::SetPlayerName(S);
}

/*void ABurnItPlayerState::SetPlayerName(FString NewPlayerName)
{
	PlayerName = NewPlayerName;
}*/

void ABurnItPlayerState::SetPlayerScore(float NewScore)
{
	PlayerScore += NewScore;
	OnPlayerScoreUpdated.Broadcast(PlayerScore);
}

void ABurnItPlayerState::SetAshes(float NewAshes)
{
	Ashes += NewAshes;
	OnAshesUpdated.Broadcast(Ashes);
}

void ABurnItPlayerState::SetObjectsBurned(float NewObjectsBurned)
{
	ObjectsBurned += NewObjectsBurned;
	OnObjectsBurnedUpdated.Broadcast(ObjectsBurned);
}
