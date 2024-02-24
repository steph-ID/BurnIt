// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurnItGameStateBase.h"
#include "Engine/GameInstance.h"
#include "BurnItGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BURNIT_API UBurnItGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:

	UFUNCTION()
	static FGuid GenerateGuid();

	UPROPERTY(BlueprintReadOnly)
	FOnGameStateChangedDelegate OnGameStateChanged;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateOnGameStateChange(EGameState NewGameState);
};
