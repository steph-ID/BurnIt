// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BurnItHUD.generated.h"

class UBurnItOverlayWrapper;
class ABurnItPlayerState;
class ABurnItCharacter;
class ABurnItPlayerController;
class UOverlayWidgetController;
class UBurnItUserWidget;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class BURNIT_API ABurnItHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UBurnItUserWidget> OverlayWidget;

	//UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	UBurnItUserWidget* GetOverlayWidget() const { return OverlayWidget; }

	UFUNCTION(BlueprintCallable)
	UBurnItOverlayWrapper* GetOverlayWrapper() const { return OverlayWrapper; }

	void InitOverlay();
	void InitIgnitionDeviceOverlay() const;
	void RemoveIgnitionDeviceOverlay() const;

protected:

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBurnItUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UBurnItOverlayWrapper> OverlayWrapper;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBurnItOverlayWrapper> OverlayWrapperClass;
/*
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	*/
};
