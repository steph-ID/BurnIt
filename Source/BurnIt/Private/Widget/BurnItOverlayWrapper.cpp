// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BurnItOverlayWrapper.h"

#include "Actor/BurnItIgnitionDevice.h"
#include "Character/BurnItCharacter.h"	
#include "Core/BurnItGameStateBase.h"
#include "Core/BurnItPlayerController.h"
#include "Core/BurnItPlayerState.h"

void UBurnItOverlayWrapper::BindCallbacksToDependencies()
{
	ABurnItPlayerState* PlayerState = GetOwningPlayerState<ABurnItPlayerState>();
	UBurnItFlammableComponent* FlammableComponent = PlayerState->GetFlammableComponent();
	IgnitionDevice = FlammableComponent->GetBurnItCharacter()->GetIgnitionDevice();

	// Callbacks for HUD value updates
	FlammableComponent->OnHealthUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateHealthOnHUD);
	PlayerState->OnAshesUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateAshesOnHUD);
	PlayerState->OnPlayerScoreUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdatePlayerScoreOnHUD);
	PlayerState->OnObjectsBurnedUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateObjectsBurnedOnHUD);

	// Callback for game popups
	OnShowSideNotificationDelegate.AddDynamic(this, &UBurnItOverlayWrapper::ShowSideNotification);
	OnShowPopupNotificationDelegate.AddDynamic(this, &UBurnItOverlayWrapper::ShowPopupNotification);

	// Only add OnFuelUpdated if the player already has an ignition device equipped
	if (IgnitionDevice != nullptr)
	{
		IgnitionDevice->OnFuelUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateFuelOnHUD);
	}

	// Subscribe to changes of the game state
	if(ABurnItGameStateBase* GS = GetWorld()->GetGameState<ABurnItGameStateBase>())
	{
		GS->OnGameStateChange.AddDynamic(this, &UBurnItOverlayWrapper::UpdateOnGameStateChange);
	}
}

void UBurnItOverlayWrapper::BindIgnitionDeviceCallbacksToDependencies()
{
	IgnitionDevice->OnFuelUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateFuelOnHUD);
}

void UBurnItOverlayWrapper::BroadcastInitialValues()
{
	const ABurnItPlayerState* PlayerState = GetOwningPlayerState<ABurnItPlayerState>();
	const UBurnItFlammableComponent* FlammableComponent = PlayerState->GetFlammableComponent();
	IgnitionDevice = FlammableComponent->GetBurnItCharacter()->GetIgnitionDevice();
	
	FlammableComponent->OnHealthUpdated.Broadcast(FlammableComponent->GetFlammableObjectData().Health, FlammableComponent->GetFlammableObjectData().MaxHealth);
	PlayerState->OnAshesUpdated.Broadcast(PlayerState->GetAshesCollected());
	PlayerState->OnPlayerScoreUpdated.Broadcast(PlayerState->GetPlayerScore());
	PlayerState->OnObjectsBurnedUpdated.Broadcast(PlayerState->GetObjectsBurned());
}

void UBurnItOverlayWrapper::BroadcastInitialIgnitionDeviceValues() const
{
	IgnitionDevice->OnFuelUpdated.Broadcast(IgnitionDevice->GetFuel(), IgnitionDevice->GetMaxFuel());
}

void UBurnItOverlayWrapper::InitializeOverlay()
{
	BindCallbacksToDependencies();
	BroadcastInitialValues();
	if (IgnitionDevice != nullptr)
	{
		BroadcastInitialIgnitionDeviceValues();
	}
}

/*void UBurnItOverlayWrapper::InitializeResultsOverlay()
{
	GetOwningPlayer()->GetPlayerState<ABurnItPlayerState>()->GetRoundData();
}*/

void UBurnItOverlayWrapper::SetIgnitionDevice(bool bIsDeviceActive)
{
	if(bIsDeviceActive)
	{
		IgnitionDevice = Cast<ABurnItCharacter>(GetOwningPlayer<ABurnItPlayerController>()->GetCharacter())->GetIgnitionDevice();
		BindIgnitionDeviceCallbacksToDependencies();
		BroadcastInitialIgnitionDeviceValues();
		AddIgnitionDeviceHUD();
	}
	else
	{
		RemoveIgnitionDeviceHUD();
		IgnitionDevice = nullptr;
	}
}

void UBurnItOverlayWrapper::UpdateOnGameStateChange(EGameState NewGameState)
{
	switch (NewGameState)
	{
	case EGameState::Waiting:
		break;
	case EGameState::Playing:
		// TODO: Update to use map based on EGameState enum
			ShowSideNotification(NotificationDataTable, "Round_Start");
		//OnShowSideNotificationDelegate.Broadcast(NotificationDataTable, "Round_Start");
		break;
	case EGameState::Ending:
		// TODO: Update to use map based on EGameState enum
			ShowSideNotification(NotificationDataTable, "Round_Complete");
		//OnShowSideNotificationDelegate.Broadcast(NotificationDataTable, "Round_Complete");
		break;
	case EGameState::GameOver:
		break;
	case EGameState::Results:
		break;
	default:
		break;
	}
}
