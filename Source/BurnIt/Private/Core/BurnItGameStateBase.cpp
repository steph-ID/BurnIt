// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BurnItGameStateBase.h"

ABurnItGameStateBase::ABurnItGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
	GameStartWaitTimer = GameStartCountdownDuration;
}

void ABurnItGameStateBase::PrepGameRound()
{
	GameState = EGameState::Waiting;

	//GetWorld()->GetTimerManager().SetTimer(GameCountdownTimerHandle, this, &ABurnItGameStateBase::StartGameRound, GameStartCountdownDuration, false);
	OnGameStateChange.Broadcast(GameState);
}

void ABurnItGameStateBase::StartGameRound()
{
	GameState = EGameState::Playing;
	OnGameStateChange.Broadcast(GameState);
}

void ABurnItGameStateBase::StartFreeRoamRound()
{
	GameState = EGameState::Playing;
	OnGameStateChange.Broadcast(GameState);
}

void ABurnItGameStateBase::LeaveRound()
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

void ABurnItGameStateBase::SetGameplayTime(float DeltaSeconds)
{
	GameplayTimer += DeltaSeconds;
}

void ABurnItGameStateBase::StartGameCountdown(float DeltaSeconds)
{
	if (GameStartWaitTimer > 0.f)
	{
		GameStartWaitTimer -= DeltaSeconds;
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("%f seconds"), GameStartWaitTimer));
	}
	else
	{
		GameState = EGameState::Playing;
		OnGameStateChange.Broadcast(GameState);
	}
}

void ABurnItGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GameState == EGameState::None)
	{
		return;
	}
	
	switch (GameState)
	{
	case EGameState::Waiting:
		StartGameCountdown(DeltaSeconds);
		break;
	case EGameState::Playing:
		SetGameplayTime(DeltaSeconds);
		break;
	case EGameState::Ending:
		break;
	case EGameState::GameOver:
		break;
	case EGameState::Results:
		break;
	default:
		break;
	}
}
