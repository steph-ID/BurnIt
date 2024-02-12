// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

USTRUCT(Blueprintable)
struct FFlammableObjectData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	float Health;
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	float MaxHealth = 100.f;
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	float AshValue = 5.f;
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	float PointValue = 10.f;
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	float Temperature=23.f;
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	float IgnitionTemperature = 250.f;
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	bool WillBurn = true;
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	bool WillMelt = false;
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	bool OnFire = false;
	
	UPROPERTY(EditAnywhere, Category = "Flammable Object")
	bool Melting = false;
};

/**
 * 
 */
UCLASS()
class BURNIT_API UItemData : public UObject
{
	GENERATED_BODY()
	
	/*
public:

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    void SetHealth(float NewHealth) { Health = NewHealth; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    void SetMaxHealth(float NewMaxHealth) { MaxHealth = NewMaxHealth; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    float GetAshValue() const { return AshValue; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    float GetPointValue() const { return PointValue; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    float GetTemperature() const { return Temperature; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    void SetTemperature(float NewTemperature) { Temperature += NewTemperature; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    float GetIgnitionTemperature() const { return IgnitionTemperature; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    bool GetWillBurn() const { return WillBurn; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    bool GetWillMelt() const { return WillMelt; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    bool GetOnFire() const { return OnFire; }

    UFUNCTION(BlueprintCallable, Category = "Flammable Object")
    bool GetMelting() const { return Melting; }*/
};
