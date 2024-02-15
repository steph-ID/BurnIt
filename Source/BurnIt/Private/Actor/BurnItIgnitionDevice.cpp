// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BurnItIgnitionDevice.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Core/BurnItPlayerController.h"
#include "Core/BurnItPlayerState.h"
#include "HUD/BurnItHUD.h"

// Sets default values
ABurnItIgnitionDevice::ABurnItIgnitionDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IgnitionDeviceSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DeviceMesh"));
	IgnitionDeviceSkeletalMesh->SetupAttachment(RootComponent);
	
	IgnitionDeviceCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	IgnitionDeviceCollision->SetupAttachment(IgnitionDeviceSkeletalMesh);
	IgnitionDeviceCollision->SetSphereRadius(32.f);
	
	FlameFxNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FlameFX"));
	FlameFxNiagaraComponent->SetupAttachment(IgnitionDeviceSkeletalMesh);
	FlameFxNiagaraComponent->SetActive(false, true);
	
	FuelDepletionTimerDelegate.BindUFunction(this, FName("SpendFuel"));

	// Default offset from the character location for projectiles to spawn
	//MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	Fuel = MaxFuel;
}

// Called when the game starts or when spawned
void ABurnItIgnitionDevice::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	IgnitionDeviceCollision->OnComponentBeginOverlap.AddDynamic(this, &ABurnItIgnitionDevice::OnSphereBeginOverlap);
}

void ABurnItIgnitionDevice::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	Character = Cast<ABurnItCharacter>(OtherActor);
	if(Character != nullptr)
	{
		AttachWeapon(Character);
		// Notify that the actor is being picked up
		//OnPickUp.Broadcast(Character);
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("overlap")));
		}*/

		// Unregister from the Overlap Event so it is no longer triggered
		IgnitionDeviceCollision->OnComponentBeginOverlap.RemoveAll(this);
	}
}

void ABurnItIgnitionDevice::AttachWeapon(ABurnItCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr || Character->GetHasDevice())
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// Set the device reference on the character and show device's HUD
	Character->SetHasDevice(true);
	Character->SetIgnitionDevice(this);
	SetIgnitionDeviceOnHUD();
	

	// Set up action bindings
	if (const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(IgnitionDeviceMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Started, this, &ABurnItIgnitionDevice::StartUsing);
			EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Completed, this, &ABurnItIgnitionDevice::StopUsing);
		}
	}
}

void ABurnItIgnitionDevice::SetIgnitionDeviceOnHUD() const
{
	if (const ABurnItPlayerController* BurnItPlayerController = Cast<ABurnItPlayerController>(Character->GetController()))
	{
		if (const ABurnItHUD* BurnItHUD = Cast<ABurnItHUD>(BurnItPlayerController->GetHUD()))
		{
			BurnItHUD->InitIgnitionDeviceOverlay();
		}
	}
}

void ABurnItIgnitionDevice::RemoveIgnitionDeviceFromHUD() const
{
	if (const ABurnItPlayerController* BurnItPlayerController = Cast<ABurnItPlayerController>(Character->GetController()))
	{
		if (const ABurnItHUD* BurnItHUD = Cast<ABurnItHUD>(BurnItPlayerController->GetHUD()))
		{
			BurnItHUD->RemoveIgnitionDeviceOverlay();
		}
	}
}

void ABurnItIgnitionDevice::StartUsing_Implementation()
{
	if(Fuel > 0)
	{
		bIsFiring = true;
		SpendFuel();
		StartFX();
		GetWorldTimerManager().SetTimer(FuelDepletionTimerHandle, FuelDepletionTimerDelegate, FuelDepletionTickRate, true, FuelDepletionTickRate);
	}
}

void ABurnItIgnitionDevice::StopUsing_Implementation()
{
	bIsFiring = false;
	StopFX();
	GetWorldTimerManager().ClearTimer(FuelDepletionTimerHandle);
}

void ABurnItIgnitionDevice::SpendFuel()
{
	if(bIsFiring)
	{
		OnDeviceTriggered.Broadcast();
		if(Fuel > 0)
		{
			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("fuel depletion of %f per %fs"), FuelDepletionValue, FuelDepletionTickRate));
			}*/
			Fuel -= FuelDepletionValue;
			OnFuelUpdated.Broadcast(Fuel, MaxFuel);
		}
		else
		{
			StopUsing();
		}
	}
	
}

void ABurnItIgnitionDevice::Reload()
{
	Fuel = MaxFuel;
	OnFuelUpdated.Broadcast(Fuel, MaxFuel);
}

void ABurnItIgnitionDevice::StartFX()
{
	if (FlameFxNiagaraComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load FlameFXSystem. Make sure reference is set in BurnItIgitionDevice blueprint."))
		return;
	}
	
	FlameFxNiagaraComponent->SetActive(true, true);
}

void ABurnItIgnitionDevice::StopFX()
{
	if (FlameFxNiagaraComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load FlameFXSystem. Make sure reference is set in BurnItIgitionDevice blueprint."))
		return;
	}
	
	FlameFxNiagaraComponent->SetActive(false, true);
}

// Called every frame
void ABurnItIgnitionDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABurnItIgnitionDevice::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}
	
	RemoveIgnitionDeviceFromHUD();
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(IgnitionDeviceMappingContext);
		}
	}
}

