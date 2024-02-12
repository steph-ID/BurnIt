// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetController/BurnItWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */
/*DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeUpdatedOneFloat, float, NewFloat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeUpdatedTwoFloat, float, NewFloat1, float, NewFloat2);*/

UCLASS(BlueprintType, Blueprintable)
class BURNIT_API UOverlayWidgetController : public UBurnItWidgetController
{
	GENERATED_BODY()

public:
	/*virtual void BroadcastInitialValues() override;
	virtual void BroadcastInitialIgnitionDeviceValues() override;
	virtual void BindCallbacksToDependencies() override;

/*	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedTwoFloat OnHealthUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnAshesUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedOneFloat OnPlayerScoreUpdated;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedTwoFloat OnFuelUpdated;

	// Event delegates
	FOnAttributeUpdated HealthUpdatedDelegateHandle;
	FOnAttributeUpdated AshesUpdatedDelegateHandle;
	FOnAttributeUpdated PlayerScoreUpdatedDelegateHandle;
	FOnAttributeUpdated FuelUpdatedDelegateHandle;

	// Functions
	UFUNCTION(BlueprintCallable)
	void UpdateHealthOnHud();

	UFUNCTION(BlueprintCallable)
	void UpdateAshesOnHud();

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerScoreOnHud();

	UFUNCTION(BlueprintCallable)
	void UpdateFuelOnHud();
	*/
};
