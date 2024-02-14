// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/BurnItPlayerState.h"
#include "Data/ItemData.h"
#include "BurnItFlammableComponent.generated.h"

class ABurnItFlammableActor;
class ABurnItCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BURNIT_API UBurnItFlammableComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flammable Object", meta = (AllowPrivateAccess = "true"))
	bool bIsPlayer = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flammable Object", meta = (AllowPrivateAccess = "true"))
	bool bIsWarmed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Flammable Object", meta = (AllowPrivateAccess = "true"))
	bool bIsOnFire = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flammable Object", meta = (AllowPrivateAccess = "true"))
	FFlammableObjectData FlammableObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flammable Object", meta = (AllowPrivateAccess = "true"))
	ABurnItPlayerState* PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Flammable Object", meta = (AllowPrivateAccess = "true"))
	float ChanceToTurnToAsh = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Flammable Object")
	float CoolingTickRate = 0.1f;

public:	
	// Sets default values for this component's properties
	UBurnItFlammableComponent();

	// Object functions
	UFUNCTION(BlueprintCallable)
	void SetFlammableObjectData(const FFlammableObjectData NewFlammableObject) { FlammableObject = NewFlammableObject; }
	
	UFUNCTION(BlueprintCallable)
	FFlammableObjectData GetFlammableObjectData() const { return FlammableObject; }
	
	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedTwoFloat OnHealthUpdated;

	/*
	 * Begin getters
	*/
	UFUNCTION(BlueprintCallable)
	ABurnItCharacter* GetBurnItCharacter() const;

	UFUNCTION(BlueprintCallable)
	ABurnItFlammableActor* GetFlammableActor() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentTemperature() const { return FlammableObject.CurrentTemperature; }

	UFUNCTION(BlueprintCallable)
	float GetBaseTemperature() const { return FlammableObject.BaseTemperature; }

	UFUNCTION(BlueprintCallable)
	float GetBurnTemperature() const { return FlammableObject.BurnTemperature; }

	UFUNCTION(BlueprintCallable)
	float GetIgnitionTemperature() const { return FlammableObject.IgnitionTemperature; }

	UFUNCTION(BlueprintCallable)
	float GetTimeUntilCooling() const { return FlammableObject.TimeUntilCooling; }
	
	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return FlammableObject.Health; }

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const { return FlammableObject.MaxHealth; }
	/*
	 * End getters
	*/

	/*
	 * Begin setters
	*/
	UFUNCTION(BlueprintCallable, Category = "Flammable Object")
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable, Category = "Flammable Object")
	void SetMaxHealth(float NewMaxHealth) { FlammableObject.MaxHealth = NewMaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Flammable Object")
	void SetCurrentTemperature(float NewCurrentTemperature) { FlammableObject.CurrentTemperature = NewCurrentTemperature; }

	UFUNCTION(BlueprintCallable, Category = "Flammable Object")
	void SetBaseTemperature(float NewBaseTemperature) { FlammableObject.BaseTemperature = NewBaseTemperature; }
	/*
	 * End setters
	*/

	UFUNCTION(BlueprintCallable, Category = "Flammable Object")
	void AdjustCurrentTemperature(float NewCurrentTemperature) { FlammableObject.CurrentTemperature += NewCurrentTemperature; }
	
	UFUNCTION(BlueprintCallable)
	void AdjustHealth(float HealthToAdd);
	
	UFUNCTION(BlueprintCallable)
	void AdjustTemperature(float TempToAdd);
	
	UFUNCTION(BlueprintCallable)
	void CatchFire();
	
	UFUNCTION(BlueprintCallable)
	void ExtinguishFire();
	
	UFUNCTION(BlueprintCallable)
	void Melt() const;
	
	UFUNCTION(BlueprintCallable)
	void Cool();
	
	UFUNCTION(BlueprintCallable)
	void Burn();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FTimerHandle BurnDamageTimerHandle;
	FTimerDelegate BurnDamageTimerDelegate;
	FTimerHandle CoolingTimerHandle;
	FTimerDelegate CoolingTimerDelegate;
	
	UFUNCTION(BlueprintCallable)
	void ProcessObjectDeath();
	
	UFUNCTION(BlueprintCallable)
	void ProcessPlayerDeath();
	
	UFUNCTION(BlueprintCallable)
	void SendPoints();
};
