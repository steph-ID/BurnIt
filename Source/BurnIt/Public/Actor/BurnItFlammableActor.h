// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurnItActor.h"
#include "Component/BurnItFlammableComponent.h"
#include "BurnItFlammableActor.generated.h"

class UBurnItFlammableComponent;

UCLASS()
class BURNIT_API ABurnItFlammableActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category="Flammable Object")
	UBurnItFlammableComponent* FlammableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Flammable Object", meta = (AllowPrivateAccess = "true"))
	float AshValue = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Flammable Object", meta = (AllowPrivateAccess = "true"))
	bool bIsOnFire = false;
	
public:	
	// Sets default values for this actor's properties
	ABurnItFlammableActor();
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABurnItActor> AshObjectClass;

	UFUNCTION(BlueprintCallable)
	UBurnItFlammableComponent* GetFlammableComponent() const { return FlammableComponent; }

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; }
	
	UFUNCTION(BlueprintCallable)
	float GetBurnTemperature() const { return GetFlammableComponent()->GetFlammableObjectData().BurnTemperature; }
	
	UFUNCTION(BlueprintNativeEvent)
	void Ignite();
	
	UFUNCTION(BlueprintNativeEvent)
	void Extinguish();
	
	UFUNCTION(BlueprintNativeEvent)
	void TurnToAsh();
	
	UFUNCTION(BlueprintNativeEvent)
	void Melt();
	
	UFUNCTION(BlueprintNativeEvent)
	void DropAsh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
