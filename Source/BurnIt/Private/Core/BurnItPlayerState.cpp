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

void ABurnItPlayerState::SetAshesCollected(float NewAshesCollected)
{
	AshesCollected += NewAshesCollected;
	OnAshesUpdated.Broadcast(AshesCollected);
}

void ABurnItPlayerState::SetObjectsBurned(float NewObjectsBurned)
{
	ObjectsBurned += NewObjectsBurned;
	OnObjectsBurnedUpdated.Broadcast(ObjectsBurned);
}

FRoundData ABurnItPlayerState::GetRoundData()
{
	FRoundData RoundData;
	
	RoundData.PlayerID = GetPlayerId();
	RoundData.PlayerName = GetPlayerName();
	RoundData.RoundTime = GetRoundTime();
	RoundData.PlayerScore = GetPlayerScore();
	RoundData.ObjectsBurned = GetObjectsBurned();
	RoundData.AshesCollected = GetAshesCollected();
	
	return RoundData;	
}
