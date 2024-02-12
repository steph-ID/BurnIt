// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BurnItPlayerState.generated.h"

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
	float PlayerScore;

	UPROPERTY()
	float Ashes;

public:
	ABurnItPlayerState();

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnAshesUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnPlayerScoreUpdated;

	UFUNCTION(BlueprintCallable)
	UBurnItFlammableComponent* GetFlammableComponent() const { return FlammableComponent; }

	/*UFUNCTION(BlueprintCallable)
	void SetFlammableObjectData(const FFlammableObjectData NewFlammableObject) { FlammableObject = NewFlammableObject; }
	//void SetFlammableObjectData(const FFlammableObjectData NewFlammableObject) const { FlammableComponent->SetFlammableObjectData(NewFlammableObject); }*/

	UFUNCTION(BlueprintCallable)
	void SetPlayerScore(float NewScore);

	UFUNCTION(BlueprintCallable)
	void SetAshes(float NewAshes);
	
	UFUNCTION(BlueprintCallable)
	int32 GetPlayerScore() const { return PlayerScore; }
	
	UFUNCTION(BlueprintCallable)
	int32 GetAshes() const { return Ashes; }
};
