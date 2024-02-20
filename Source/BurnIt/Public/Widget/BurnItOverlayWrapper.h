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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShowGameNotification, UDataTable*, DataTable, FName, RowName);

UCLASS()
class BURNIT_API UBurnItOverlayWrapper : public UBurnItUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UDataTable* NotificationDataTable = nullptr;

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

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnShowGameNotification OnShowGameNotification;

	// Functions to update attributes on HUD
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthOnHUD(float NewHealth, float NewMaxHealth);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFuelOnHUD(float NewFuel, float NewMaxFuel);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAshesOnHUD(float NewAshes);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePlayerScoreOnHUD(float NewPlayerScore);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateObjectsBurnedOnHUD(float NewObjectsBurned);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowGameNotification(UDataTable* DataTable, FName RowName);
	
	UFUNCTION(BlueprintCallable)
	void UpdateOnGameStateChange(EGameState NewGameState);
};
