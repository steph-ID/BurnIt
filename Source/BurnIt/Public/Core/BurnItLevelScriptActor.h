// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BurnItLevelScriptActor.generated.h"

UENUM(BlueprintType)
enum class ELevelType : uint8
{
	None			UMETA(DisplayName = "None"),
	Menu			UMETA(DisplayName = "Menu"),
	Gameplay		UMETA(DisplayName = "Gameplay"),
	FreeRoam		UMETA(DisplayName = "Free Roam")
};

/**
 * 
 */
UCLASS()
class BURNIT_API ABurnItLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level", meta=(AllowPrivateAccess="true"))
	ELevelType LevelType = ELevelType::None;

public:
	ABurnItLevelScriptActor();
	
	virtual void BeginPlay() override;
};
