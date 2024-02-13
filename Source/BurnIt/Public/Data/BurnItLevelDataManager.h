// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurnItLevelDataManager.generated.h"

/**
 * 
 */
UCLASS()
class BURNIT_API ABurnItLevelDataManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float AmbientTemperature = 20.f;

	UPROPERTY(VisibleAnywhere)
	float TargetAmbientTemperature;

	UPROPERTY(EditAnywhere)
	float TemperatureChangeTickRate = 0.25f;

	UPROPERTY(EditAnywhere)
	UCurveFloat* TemperatureChangeRamp;

public:
	ABurnItLevelDataManager();
	
	UFUNCTION(BlueprintCallable)
	void SetAmbientTemperature(const float NewAmbientTemperature) { TargetAmbientTemperature = NewAmbientTemperature; }
	
	UFUNCTION(BlueprintCallable)
	float GetAmbientTemperature() { return AmbientTemperature; }
	
	UFUNCTION(BlueprintNativeEvent)
	void AdjustAmbientTemperature();

private:

	FTimerHandle TemperatureChangeTimerHandle;
	FTimerDelegate TemperatureChangeTimerDelegate;
};
