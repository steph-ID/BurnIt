// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurnItActor.h"
#include "Component/BurnItFlammableComponent.h"
#include "GameFramework/Actor.h"
#include "BurnItFlammableActor.generated.h"

UCLASS()
class BURNIT_API ABurnItFlammableActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flammable Object", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Flammable Object", meta = (AllowPrivateAccess = "true"))
	float ChanceToTurnToAsh = 0.2f;

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
	
	UFUNCTION(BlueprintNativeEvent)
	void Ignite();
	
	UFUNCTION(BlueprintCallable)
	void StartBurning(float BurnDamage);
	
	UFUNCTION(BlueprintCallable)
	void StopBurning();
	
	UFUNCTION(BlueprintCallable)
	void Burn(float BurnDamage);
	
	UFUNCTION(BlueprintNativeEvent)
	void TurnToAsh();
	
	UFUNCTION(BlueprintNativeEvent)
	void Melt();
	
	UFUNCTION(BlueprintNativeEvent)
	void DropAsh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UBurnItFlammableComponent* FlammableComponent;

private:
	FTimerDelegate BurnDamageTimerDelegate;
	FTimerHandle BurnDamageTimerHandle;
};
