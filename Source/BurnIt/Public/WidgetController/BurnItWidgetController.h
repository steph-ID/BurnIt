// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/BurnItIgnitionDevice.h"
#include "Character/BurnItCharacter.h"
#include "BurnItWidgetController.generated.h"

class ABurnItPlayerController;
class ABurnItPlayerState;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS)
	: PlayerController(PC),
	PlayerState(PS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AController> PlayerController = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBurnItFlammableComponent> FlammableComponent = nullptr;
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFlammableObjectData& FlammableCharacterData;*/
};

/**
 * 
 */
UCLASS()
class BURNIT_API UBurnItWidgetController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	void SetIgnitionDevice(bool bIsDeviceActive);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BroadcastInitialIgnitionDeviceValues();
	virtual void BindCallbacksToDependencies();
	
protected:

	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<ABurnItPlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<ABurnItPlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<ABurnItCharacter> Character;

	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<UBurnItFlammableComponent> FlammableComponent;

	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<ABurnItIgnitionDevice> IgnitionDevice;

	/*UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	FFlammableObjectData& FlammableCharacterData;*/
};
