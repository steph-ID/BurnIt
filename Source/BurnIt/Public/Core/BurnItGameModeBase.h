// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BurnItGameModeBase.generated.h"

	
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStart);

/**
 * 
 */
UCLASS()
class BURNIT_API ABurnItGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	FGameStart GameStart;

public:
};
