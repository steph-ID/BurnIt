// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BurnItPlayerState.h"

#include "Component/BurnItFlammableComponent.h"

ABurnItPlayerState::ABurnItPlayerState()
{
	FlammableComponent = CreateDefaultSubobject<UBurnItFlammableComponent>(TEXT("FlammableComponent"));
}

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
