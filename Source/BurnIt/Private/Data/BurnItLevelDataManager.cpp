// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/BurnItLevelDataManager.h"

ABurnItLevelDataManager::ABurnItLevelDataManager()
{
	TargetAmbientTemperature = AmbientTemperature;
	
	TemperatureChangeTimerDelegate.BindUFunction(this, FName("AdjustAmbientTemperature"));
}

void ABurnItLevelDataManager::AdjustAmbientTemperature_Implementation()
{
	/*while (AmbientTemperature != TargetAmbientTemperature)
	{
		float TemperatureRampPosition = TemperatureChangeRamp->GetFloatValue(TemperatureChangeTime);
		AmbientTemperature = FMath::Lerp(AmbientTemperature, TargetAmbientTemperature, TemperatureRampPosition);
	}*/
}
