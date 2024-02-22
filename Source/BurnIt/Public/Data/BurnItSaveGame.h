// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "GameFramework/SaveGame.h"
#include "BurnItSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Data")
	int32 ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Data")
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Data")
	FFlammableObjectData FlammablePlayerData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Data")
	float AshesCurrency;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Data")
	float TotalObjectsBurned;
};

USTRUCT(BlueprintType)
struct FIgnitionDevice
{
	GENERATED_BODY()

	int32 ID;
	FString Name;
};

USTRUCT(BlueprintType)
struct FRoundData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Round Data")
	int32 PlayerID = 1000;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Round Data")
	FString PlayerName = "";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Round Data")
	float PlayerScore = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Round Data")
	float RoundTime = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Round Data")
	float ObjectsBurned = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Round Data")
	float AshesCollected = 0.f;
};

USTRUCT(BlueprintType)
struct FTrophy
{
	GENERATED_BODY()

	FString Name;
	FString Description;
};

USTRUCT(BlueprintType)
struct FAchievement
{
	GENERATED_BODY()

	FString Name;
	FString Description;
};

/**
 * 
 */
UCLASS()
class BURNIT_API UBurnItSaveGame : public USaveGame
{
	GENERATED_BODY()

	/*TArray<FRoundData> PlayerRoundHistory;
	TArray<FAchievement> PlayerAchievements;
	TArray<FTrophy> PlayerTrophies;*/
};
