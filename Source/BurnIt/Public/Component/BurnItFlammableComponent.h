// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/BurnItPlayerState.h"
#include "Data/ItemData.h"
#include "BurnItFlammableComponent.generated.h"


class ABurnItCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BURNIT_API UBurnItFlammableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBurnItFlammableComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flammable Object")
	bool IsPlayer = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flammable Object")
	FFlammableObjectData FlammableObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flammable Object")
	ABurnItPlayerState* PlayerState = nullptr;

	// Object functions
	UFUNCTION(BlueprintCallable)
	void SetFlammableObjectData(const FFlammableObjectData NewFlammableObject) { FlammableObject = NewFlammableObject; }
	
	UFUNCTION(BlueprintCallable)
	FFlammableObjectData GetFlammableObjectData() const { return FlammableObject; }
	
	UFUNCTION(BlueprintCallable)
	float GetBurnTemperature() const { return FlammableObject.BurnTemperature; }
	
	UFUNCTION(BlueprintCallable)
	ABurnItCharacter* GetBurnItCharacter() const;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedTwoFloat OnHealthUpdated;

	/*
	 * Begin getters
	 */

	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return FlammableObject.Health; }

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const { return FlammableObject.MaxHealth; }

	/*
	 * End getters
	*/


	UFUNCTION(BlueprintCallable, Category = "Flammable Object")
	void SetMaxHealth(float NewMaxHealth) { FlammableObject.MaxHealth = NewMaxHealth; }
	
	UFUNCTION(BlueprintCallable)
	void AdjustHealth(float HealthToAdd);
	
	UFUNCTION(BlueprintCallable)
	void AdjustTemperature(float TempToAdd);
	
	UFUNCTION(BlueprintCallable)
	void CatchFire() const;
	
	UFUNCTION(BlueprintCallable)
	void Melt() const;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void ProcessObjectDeath();
	
	UFUNCTION(BlueprintCallable)
	void ProcessPlayerDeath();
	
	UFUNCTION(BlueprintCallable)
	void SendPoints();
};
