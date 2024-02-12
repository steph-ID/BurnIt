// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BurnItOverlayWrapper.h"

#include "Actor/BurnItIgnitionDevice.h"
#include "Character/BurnItCharacter.h"	
#include "Core/BurnItPlayerController.h"
#include "Core/BurnItPlayerState.h"

void UBurnItOverlayWrapper::BindCallbacksToDependencies()
{
	ABurnItPlayerState* PlayerState = GetOwningPlayerState<ABurnItPlayerState>();
	UBurnItFlammableComponent* FlammableComponent = PlayerState->GetFlammableComponent();
	IgnitionDevice = FlammableComponent->GetBurnItCharacter()->GetIgnitionDevice();
	
	FlammableComponent->OnHealthUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateHealthOnHUD);
	PlayerState->OnAshesUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateAshesOnHUD);
	PlayerState->OnPlayerScoreUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdatePlayerScoreOnHUD);

	// Only add OnFuelUpdated if the player has an ignition device equipped
	if (IgnitionDevice != nullptr)
	{
		IgnitionDevice->OnFuelUpdated.AddDynamic(this, &UBurnItOverlayWrapper::UpdateFuelOnHUD);
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
