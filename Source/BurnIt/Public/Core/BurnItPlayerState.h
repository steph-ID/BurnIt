// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/BurnItSaveGame.h"
#include "GameFramework/PlayerState.h"
#include "BurnItPlayerState.generated.h"

class UBurnItFlammableComponent;
class UBurnItSaveGame;

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeUpdatedOneFloat, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeUpdatedTwoFloat, float, NewValue1, float, NewValue2);

UCLASS()
class BURNIT_API ABurnItPlayerState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UBurnItFlammableComponent* FlammableComponent;

	UPROPERTY()
	FRoundData CurrentRoundData;

	UPROPERTY()
	FPlayerData PlayerData;

public:
	ABurnItPlayerState();

	UFUNCTION(BlueprintCallable)
	void SetDisplayName();

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnAshesUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnPlayerScoreUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnObjectsBurnedUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnAshesCurrencyUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnTotalObjectsBurnedUpdated;

	UFUNCTION(BlueprintCallable)
	UBurnItFlammableComponent* GetFlammableComponent() const { return FlammableComponent; }

	/*UFUNCTION(BlueprintCallable)
	void SetFlammableObjectData(const FFlammableObjectData NewFlammableObject) { FlammableObject = NewFlammableObject; }
	//void SetFlammableObjectData(const FFlammableObjectData NewFlammableObject) const { FlammableComponent->SetFlammableObjectData(NewFlammableObject); }*/
	
	/*UFUNCTION(BlueprintCallable)
	int32 SetPlayerID(int32 NewPlayerID) { PlayerID = NewPlayerID; };*/

	UFUNCTION(BlueprintCallable)
	void SetAshesCurrency(float NewAshes);
	
	UFUNCTION(BlueprintCallable)
	void SetTotalObjectsBurned(float NewObject);

	UFUNCTION(BlueprintCallable)
	void SetPlayerScore(float NewScore);

	UFUNCTION(BlueprintCallable)
	void SetAshesCollected(float NewAshesCollected);

	UFUNCTION(BlueprintCallable)
	void SetObjectsBurned(float NewObjectsBurned);
	
	UFUNCTION(BlueprintCallable)
	void SetRoundTime(float NewRoundTime) { CurrentRoundData.RoundTime = NewRoundTime; }
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerData(FPlayerData NewPlayerData) { PlayerData = NewPlayerData; }
	
/*	UFUNCTION(BlueprintCallable)
	FString GetPlayerName() const { return PlayerName; }*/
	
	UFUNCTION(BlueprintCallable)
	float GetAshesCurrency() const { return PlayerData.AshesCurrency; }
	
	UFUNCTION(BlueprintCallable)
	float GetTotalObjectsBurned() const { return PlayerData.TotalObjectsBurned; }
	
	UFUNCTION(BlueprintCallable)
	float GetPlayerScore() const { return CurrentRoundData.PlayerScore; }
	
	UFUNCTION(BlueprintCallable)
	float GetAshesCollected() const { return CurrentRoundData.AshesCollected; }
	
	UFUNCTION(BlueprintCallable)
	float GetObjectsBurned() const { return CurrentRoundData.ObjectsBurned; }
	
	UFUNCTION(BlueprintCallable)
	float GetGameplayTime();
	
	UFUNCTION(BlueprintCallable)
	FRoundData GetRoundData();

	UFUNCTION(BlueprintCallable)
	FPlayerData GetPlayerData();
};
