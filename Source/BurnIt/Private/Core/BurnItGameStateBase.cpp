// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BurnItGameStateBase.h"

void ABurnItGameStateBase::PrepGame()
{
	GameState = EGameState::Waiting;
	StartGameCountdown(GameCountdownDuration);

	GetWorld()->GetTimerManager().SetTimer(GameCountdownTimerHandle, this, &ABurnItGameStateBase::StartGame, GameCountdownDuration, false);
	OnGameStateChange.Broadcast(GameState);
}

void ABurnItGameStateBase::StartGame()
{
	GameState = EGameState::Playing;
	SetGameplayTime();
	OnGameStateChange.Broadcast(GameState);
}

void ABurnItGameStateBase::EndGame()
{
	GameState = EGameState::Results;
	OnGameStateChange.Broadcast(GameState);
}

void ABurnItGameStateBase::FuelDepleted()
{
	GameState = EGameState::Ending;
	OnGameStateChange.Broadcast(GameState);
}

void ABurnItGameStateBase::PlayerDied()
{
	GameState = EGameState::GameOver;
	OnGameStateChange.Broadcast(GameState);
}

void ABurnItGameStateBase::SetGameplayTime()
{
	GameplayTimer += GetServerWorldTimeSeconds();
}

void ABurnItGameStateBase::StopGameplayTimer()
{
}

void ABurnItGameStateBase::StartGameCountdown(float Seconds)
{
}
