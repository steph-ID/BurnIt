// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BurnItOverlayWrapper.h"

#include "Actor/BurnItIgnitionDevice.h"
#include "Character/BurnItCharacter.h"	
#include "Core/BurnItGameModeBase.h"
#include "Core/BurnItGameStateBase.h"
#include "Core/BurnItPlayerController.h"
#include "Core/BurnItPlayerState.h"
#include "Kismet/GameplayStatics.h"

void UBurnItOverlayWrapper::BindCallbacksToDependencies()
{
	ABurnItPlayerState* PlayerState = GetOwningPlayerState<ABurnItPlayerState>();
	UBurnItFlammableComponent* FlammableComponent = PlayerState->GetFlammableComponent();
	IgnitionDevice = FlammableComponent->GetBurnItCharacter()->GetIgnitionDevice();
	
	FlammableComponent->OnHealthUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateHealthOnHUD);
	PlayerState->OnAshesUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateAshesOnHUD);
	PlayerState->OnPlayerScoreUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdatePlayerScoreOnHUD);
	PlayerState->OnObjectsBurnedUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateObjectsBurnedOnHUD);

	// Only add OnFuelUpdated if the player has an ignition device equipped
	if (IgnitionDevice != nullptr)
	{
		IgnitionDevice->OnFuelUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateFuelOnHUD);
	}
	if(ABurnItGameStateBase* GS = Cast<ABurnItGameStateBase>(UGameplayStatics::GetGameState(this)))
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
	PlayerState->OnAshesUpdated.Broadcast(PlayerState->GetAshes());
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
		break;
	case EGameState::Ending:
		break;
	case EGameState::GameOver:
		break;
	case EGameState::Results:
		break;
	default:
		break;
	}
}
