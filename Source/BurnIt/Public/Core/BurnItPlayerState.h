// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BurnItPlayerState.generated.h"

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

class UBurnItFlammableComponent;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeUpdatedOneFloat, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeUpdatedTwoFloat, float, NewValue1, float, NewValue2);

UCLASS()
class BURNIT_API ABurnItPlayerState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY()
	UBurnItFlammableComponent* FlammableComponent;

	/*UPROPERTY()
	FFlammableObjectData FlammableObject;*/

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	float PlayerScore;

	UPROPERTY()
	float AshesCollected;

	UPROPERTY()
	float ObjectsBurned;

	UPROPERTY()
	float RoundTime;

public:
	ABurnItPlayerState();

	virtual void SetPlayerName(const FString& S) override;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnAshesUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnPlayerScoreUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnObjectsBurnedUpdated;

	UFUNCTION(BlueprintCallable)
	UBurnItFlammableComponent* GetFlammableComponent() const { return FlammableComponent; }

	/*UFUNCTION(BlueprintCallable)
	void SetFlammableObjectData(const FFlammableObjectData NewFlammableObject) { FlammableObject = NewFlammableObject; }
	//void SetFlammableObjectData(const FFlammableObjectData NewFlammableObject) const { FlammableComponent->SetFlammableObjectData(NewFlammableObject); }*/
	
	/*UFUNCTION(BlueprintCallable)
	int32 SetPlayerID(int32 NewPlayerID) { PlayerID = NewPlayerID; };*/

	UFUNCTION(BlueprintCallable)
	void SetPlayerScore(float NewScore);

	UFUNCTION(BlueprintCallable)
	void SetAshesCollected(float NewAshesCollected);

	UFUNCTION(BlueprintCallable)
	void SetObjectsBurned(float NewObjectsBurned);
	
	UFUNCTION(BlueprintCallable)
	void SetRoundTime(float NewRoundTime) { RoundTime = NewRoundTime; }
	
/*	UFUNCTION(BlueprintCallable)
	FString GetPlayerName() const { return PlayerName; }*/
	
	UFUNCTION(BlueprintCallable)
	float GetPlayerScore() const { return PlayerScore; }
	
	UFUNCTION(BlueprintCallable)
	float GetRoundTime() const { return RoundTime; }
	
	UFUNCTION(BlueprintCallable)
	float GetAshesCollected() const { return AshesCollected; }
	
	UFUNCTION(BlueprintCallable)
	float GetObjectsBurned() const { return ObjectsBurned; }
	
	UFUNCTION(BlueprintCallable)
	FRoundData GetRoundData();
};
