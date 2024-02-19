// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/BurnItUserWidget.h"
#include "BurnItOverlayWrapper.generated.h"

enum class EGameState : uint8;
class ABurnItIgnitionDevice;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributeUpdated);

UCLASS()
class BURNIT_API UBurnItOverlayWrapper : public UBurnItUserWidget
{
	GENERATED_BODY()

public:
	
	void BroadcastInitialValues();
	void BroadcastInitialIgnitionDeviceValues() const;
	void BindIgnitionDeviceCallbacksToDependencies();
	void BindCallbacksToDependencies();
	void InitializeOverlay();
	
	UFUNCTION(BlueprintCallable)
	void SetIgnitionDevice(bool bIsDeviceActive);
	
	UFUNCTION(BlueprintImplementableEvent)
	void AddIgnitionDeviceHUD();
	
	UFUNCTION(BlueprintImplementableEvent)
	void RemoveIgnitionDeviceHUD();

	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<ABurnItIgnitionDevice> IgnitionDevice;

	// Event delegates
	/*FOnAttributeUpdated HealthUpdatedDelegateHandle;
	FOnAttributeUpdated AshesUpdatedDelegateHandle;
	FOnAttributeUpdated PlayerScoreUpdatedDelegateHandle;
	FOnAttributeUpdated FuelUpdatedDelegateHandle;
	FOnAttributeUpdated ObjectsBurnedUpdatedDelegateHandle;*/

	// Functions to update attributes on HUD
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateHealthOnHUD(float NewHealth, float NewMaxHealth);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFuelOnHUD(float NewFuel, float NewMaxFuel);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateAshesOnHUD(float NewAshes);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdatePlayerScoreOnHUD(float NewPlayerScore);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateObjectsBurnedOnHUD(float NewObjectsBurned);
	
	UFUNCTION(BlueprintCallable)
	void UpdateOnGameStateChange(EGameState NewGameState);
};
