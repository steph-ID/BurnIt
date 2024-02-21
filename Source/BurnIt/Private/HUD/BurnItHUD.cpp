// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BurnItHUD.h"

#include "Widget/BurnItOverlayWrapper.h"
#include "Widget/BurnItUserWidget.h"

void ABurnItHUD::InitOverlay()
{
	// Construct widget controller & widget, set widget's widget controller, add to viewport
	checkf(OverlayClass, TEXT("OverlayClass uninitialized, please fill out BP_BurnItHUD"));

	// Create a new wrapper widget
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), OverlayClass);
	OverlayWidget = Cast<UBurnItOverlayWrapper>(Widget);
	
	// Set current values on HUD's widgets
	Cast<UBurnItOverlayWrapper>(OverlayWidget)->InitializeOverlay();

	// Add overlay to viewport
	Widget->AddToViewport();
}

void ABurnItHUD::InitIgnitionDeviceOverlay() const
{
	Cast<UBurnItOverlayWrapper>(OverlayWidget)->SetIgnitionDevice(true);
}

void ABurnItHUD::RemoveIgnitionDeviceOverlay() const
{
	Cast<UBurnItOverlayWrapper>(OverlayWidget)->SetIgnitionDevice(false);
}

void ABurnItHUD::DisplayRoundResults()
{
	if (OverlayWidget)
	{
		OverlayWidget->RemoveFromParent();
	}

	checkf(ResultsOverlayClass, TEXT("ResultsOverlayClass uninitialized, please fill out BP_BurnItHUD"));
	
	// Create a new wrapper widget
	UUserWidget* Widget = CreateWidget<UBurnItUserWidget>(GetOwningPlayerController(), ResultsOverlayClass);
	
	Widget->AddToViewport();
}


/*
 * Old code based on GAS implementation
 * 
UOverlayWidgetController* ABurnItHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		
		// Bind to delegates for listening for attribute changes
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void ABurnItHUD::InitOverlay(APlayerController* PC, APlayerState* PS)
{
	// Construct widget controller & widget, set widget's widget controller, add to viewport

	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized, please fill out BP_BurnItHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized, please fill out BP_BurnItHUD"));

	Character = Cast<ABurnItCharacter>(PC->GetCharacter());
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UBurnItUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	//Cast<UBurnItUserWidget>(Widget)->SetWidgetController(WidgetController);
	//OverlayWidget->WidgetControllerSet();
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}*/
