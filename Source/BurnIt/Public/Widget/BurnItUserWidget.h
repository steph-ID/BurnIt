// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BurnItUserWidget.generated.h"

/**
 * 
*/

UCLASS()
class BURNIT_API UBurnItUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

protected:
	
};
