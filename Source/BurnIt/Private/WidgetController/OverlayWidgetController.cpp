// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/OverlayWidgetController.h"

#include "Core/BurnItPlayerState.h"

/*
void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthUpdated.Broadcast(FlammableComponent->GetHealth(), FlammableComponent->GetMaxHealth());
	OnAshesUpdated.Broadcast(PlayerState->GetAshes());
	OnPlayerScoreUpdated.Broadcast(PlayerState->GetPlayerScore());
}
void UOverlayWidgetController::BroadcastInitialIgnitionDeviceValues()
{
	OnFuelUpdated.Broadcast(IgnitionDevice->GetFuel(), IgnitionDevice->GetMaxFuel());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	PlayerState->HealthUpdatedDelegateHandle.AddLambda([this]()
	{
		OnHealthUpdated.Broadcast(FlammableComponent->GetHealth(), FlammableComponent->GetMaxHealth());
	});
	PlayerState->AshesUpdatedDelegateHandle.AddLambda([this]()
	{
		OnAshesUpdated.Broadcast(PlayerState->GetAshes());
	});
	PlayerState->PlayerScoreUpdatedDelegateHandle.AddLambda([this]()
	{
		OnPlayerScoreUpdated.Broadcast(PlayerState->GetPlayerScore());
	});
	PlayerState->FuelUpdatedDelegateHandle.AddLambda([this]()
	{
		OnFuelUpdated.Broadcast(IgnitionDevice->GetFuel(), IgnitionDevice->GetMaxFuel());
	});
}

/*void UOverlayWidgetController::UpdateHealthOnHud()
{
	OnHealthUpdated.Broadcast(FlammableComponent->GetHealth(), FlammableComponent->GetMaxHealth());
}

void UOverlayWidgetController::UpdateAshesOnHud()
{
	OnAshesUpdated.Broadcast(PlayerState->GetAshes());
}

void UOverlayWidgetController::UpdatePlayerScoreOnHud()
{
	OnPlayerScoreUpdated.Broadcast(PlayerState->GetPlayerScore());
}

void UOverlayWidgetController::UpdateFuelOnHud()
{
	OnFuelUpdated.Broadcast(IgnitionDevice->GetFuel(), IgnitionDevice->GetMaxFuel());
}*/
