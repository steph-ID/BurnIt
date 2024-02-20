// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BurnItLevelScriptActor.h"

#include "Core/BurnItGameStateBase.h"

ABurnItLevelScriptActor::ABurnItLevelScriptActor()
{
}

void ABurnItLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
	switch (LevelType)
	{
	case ELevelType::Menu:
		break;
	case ELevelType::Gameplay:
		GetWorld()->GetGameState<ABurnItGameStateBase>()->PrepGameRound();
		break;
	case ELevelType::FreeRoam:
		GetWorld()->GetGameState<ABurnItGameStateBase>()->StartGameRound();
		break;
	default:
		break;
	}
}
