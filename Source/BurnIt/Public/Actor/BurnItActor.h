// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BurnItActor.generated.h"

UCLASS()
class BURNIT_API ABurnItActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABurnItActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*FUNCTION(BlueprintCallable)
	void PickUpItem();*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	
};
