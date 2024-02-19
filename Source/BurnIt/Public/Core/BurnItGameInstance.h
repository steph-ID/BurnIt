// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BurnItGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BURNIT_API UBurnItGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void NotifyGameStateOfFuelDepletion();
};
