// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BurnItPlayerState.h"

#include "Data/BurnItSaveGame.h"
#include "Component/BurnItFlammableComponent.h"
#include "Core/BurnItGameStateBase.h"

ABurnItPlayerState::ABurnItPlayerState()
{
	FlammableComponent = CreateDefaultSubobject<UBurnItFlammableComponent>(TEXT("FlammableComponent"));
}

void ABurnItPlayerState::SetDisplayName()
{
	PlayerData.Name = GetPlayerName();
}

/*void ABurnItPlayerState::SetPlayerName(FString NewPlayerName)
{
	PlayerData.PlayerName = NewPlayerName;
}*/

void ABurnItPlayerState::SetAshesCurrency(float NewAshes)
{
	PlayerData.AshesCurrency += NewAshes;
	OnAshesCurrencyUpdated.Broadcast(PlayerData.AshesCurrency);
}

void ABurnItPlayerState::SetTotalObjectsBurned(float NewObject)
{
	PlayerData.TotalObjectsBurned += NewObject;
	OnTotalObjectsBurnedUpdated.Broadcast(PlayerData.TotalObjectsBurned);
}

void ABurnItPlayerState::SetPlayerScore(float NewScore)
{
	CurrentRoundData.PlayerScore += NewScore;
	OnPlayerScoreUpdated.Broadcast(CurrentRoundData.PlayerScore);
}

void ABurnItPlayerState::SetAshesCollected(float NewAshesCollected)
{
	CurrentRoundData.AshesCollected += NewAshesCollected;
	OnAshesUpdated.Broadcast(CurrentRoundData.AshesCollected);
}

void ABurnItPlayerState::SetObjectsBurned(float NewObjectsBurned)
{
	CurrentRoundData.ObjectsBurned += NewObjectsBurned;
	OnObjectsBurnedUpdated.Broadcast(CurrentRoundData.ObjectsBurned);
}

float ABurnItPlayerState::GetGameplayTime()
{
	const ABurnItGameStateBase* GS = GetWorld()->GetGameState<ABurnItGameStateBase>();
	return GS->GetGameplayTimer();
}

FRoundData ABurnItPlayerState::GetRoundData()
{
	SetTotalObjectsBurned(GetObjectsBurned());
	SetAshesCurrency(GetAshesCollected());
	
	CurrentRoundData.PlayerID = GetPlayerId();
	CurrentRoundData.PlayerName = GetPlayerName();
	CurrentRoundData.RoundTime = GetGameplayTime();
	
	return CurrentRoundData;
}

FPlayerData ABurnItPlayerState::GetPlayerData()
{
	PlayerData.FlammablePlayerData = FlammableComponent->GetFlammableObjectData();
	
	return PlayerData;
}
