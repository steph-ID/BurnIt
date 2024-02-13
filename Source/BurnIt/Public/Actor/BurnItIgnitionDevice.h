// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Character/BurnItCharacter.h"
#include "Components/SphereComponent.h"
#include "BurnItIgnitionDevice.generated.h"

UENUM(BlueprintType)
enum class EIgnitionDeviceType : uint8
{
	None			UMETA(DisplayName = "None"),
	Match 			UMETA(DisplayName = "Match"),
	Candle 			UMETA(DisplayName = "Candle"),
	Lighter			UMETA(DisplayName = "Lighter"),
	Torch			UMETA(DisplayName = "Torch"),
	Flamethrower	UMETA(DisplayName = "Flamethrower")
};

// Declaration of the delegate that will be called when someone picks this up
// The character picking this up is the parameter sent with the notification
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, ABurnItCharacter*, PickUpCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeviceTraceDelegate);

UCLASS()
class BURNIT_API ABurnItIgnitionDevice : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ignition Device", meta = (AllowPrivateAccess = "true"))
	USphereComponent* IgnitionDeviceCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ignition Device", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* IgnitionDeviceSkeletalMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ignition Device|FX", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* FlameFxNiagaraComponent;
	
public:	
	ABurnItIgnitionDevice();
	
	virtual void Tick(float DeltaTime) override;
	
	void RemoveIgnitionDeviceFromHUD() const;
	void SetIgnitionDeviceOnHUD() const;

	UPROPERTY(BlueprintAssignable, Category="Burn It|HUD Update Events")
	FOnAttributeUpdatedTwoFloat OnFuelUpdated;
	
	/*
	 * Begin device specific variables
	 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device")
	EIgnitionDeviceType DeviceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device|Fuel")
	float Fuel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device|Fuel")
	float MaxFuel = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device|Fuel")
	float FuelDepletionValue = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device|Fuel")
	float FuelDepletionTickRate = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device|CurrentTemperature")
	float Temperature=1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device|CurrentTemperature")
	UCurveFloat* DeviceHeatRamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device")
	float FlameRange=300.f;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device|FX")
	USoundBase* DeviceSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device|FX")
	UAnimMontage* DeviceAnimation;

	/** Gun muzzle's offset from the characters location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device|FX")
	FVector MuzzleOffset; */
	
	/*
	 * End device specific variables
	*/

	UFUNCTION(BlueprintCallable, Category="Ignition Device")
	float GetFuel() const { return Fuel; }

	UFUNCTION(BlueprintCallable, Category="Ignition Device")
	float GetMaxFuel() const { return MaxFuel; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ignition Device")
	bool bIsFiring = false;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ignition Device|Input", meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* IgnitionDeviceMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ignition Device|Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* UseAction;

	// Blueprint Event Dispatcher
	UPROPERTY(BlueprintAssignable, Category = "Ignition Device|Events")
	FDeviceTraceDelegate OnDeviceTriggered;

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Ignition Device")
	void AttachWeapon(ABurnItCharacter* TargetCharacter);
	
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FOnPickUp OnPickUp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * Begin device use functions
	 */
	
	UFUNCTION(BlueprintCallable)
	void StartUsing();

	UFUNCTION(BlueprintCallable)
	void StopUsing();

	UFUNCTION(BlueprintCallable)
	void SpendFuel();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void StartFX();

	UFUNCTION(BlueprintCallable)
	void StopFX();
	
	/*
	 * End device use functions
	 */

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	UNiagaraComponent* GetFlameFxNiagaraComponent() const { return FlameFxNiagaraComponent; }

private:
	FTimerDelegate FuelDepletionTimerDelegate;
	FTimerHandle FuelDepletionTimerHandle;
	
	/** The Character holding this weapon*/
	ABurnItCharacter* Character;
};
