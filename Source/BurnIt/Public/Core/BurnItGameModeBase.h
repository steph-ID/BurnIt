// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BurnItGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	None		UMETA(DisplayName = "None"),
	Waiting		UMETA(DisplayName = "Waiting"),
	Playing		UMETA(DisplayName = "Playing"),
	Ending		UMETA(DisplayName = "Ending"),
	Results		UMETA(DisplayName = "Results"),
	GameOver	UMETA(DisplayName = "GameOver"),
};
	
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStart);

/**
 * 
 */
UCLASS()
class BURNIT_API ABurnItGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	FGameStart GameStart;

public:
};
