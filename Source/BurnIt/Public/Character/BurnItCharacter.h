// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Component/BurnItFlammableComponent.h"
#include "GameFramework/Character.h"
#include "BurnItCharacter.generated.h"

class ABurnItIgnitionDevice;

UCLASS()
class BURNIT_API ABurnItCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> LookAtSensor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float DefaultWalkSpeed = 500.f;
	//float DefaultRunSpeed = 750.f;

public:
	// Sets default values for this character's properties
	ABurnItCharacter();

	UFUNCTION(BlueprintCallable)
	UBurnItFlammableComponent* GetFlammableComponent() const { return FlammableComponent; }

	UFUNCTION(BlueprintCallable)
	ABurnItIgnitionDevice* GetIgnitionDevice() const { return IgnitionDevice; }

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasDevice;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasDevice(bool bNewHasDevice);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasDevice() const { return bHasDevice; };
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetIgnitionDevice(ABurnItIgnitionDevice* NewIgnitionDevice);
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UBurnItFlammableComponent* FlammableComponent;

	UPROPERTY()
	ABurnItIgnitionDevice* IgnitionDevice;

	UFUNCTION()
	void SetSprintSpeed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetInitialConfig();

	/** Returns Mesh1P subobject **/
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
};
