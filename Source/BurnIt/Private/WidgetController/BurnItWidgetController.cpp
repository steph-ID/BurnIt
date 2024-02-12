// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/BurnItWidgetController.h"

#include "Core/BurnItPlayerController.h"
#include "Core/BurnItPlayerState.h"

void UBurnItWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = Cast<ABurnItPlayerController>(WCParams.PlayerController);
	PlayerState = Cast<ABurnItPlayerState>(WCParams.PlayerState);
	Character = Cast<ABurnItCharacter>(PlayerController->GetCharacter());
	FlammableComponent = Character->GetFlammableComponent();
}

void UBurnItWidgetController::SetIgnitionDevice(const bool bIsDeviceActive)
{
	if(bIsDeviceActive)
	{
		IgnitionDevice = Character->GetIgnitionDevice();
	}
	else
	{
		IgnitionDevice = nullptr;
	}
}

void UBurnItWidgetController::BroadcastInitialValues()
{
}

void UBurnItWidgetController::BroadcastInitialIgnitionDeviceValues()
{
}

void UBurnItWidgetController::BindCallbacksToDependencies()
{
}
