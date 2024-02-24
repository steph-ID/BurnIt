// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BurnItCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Core/BurnItPlayerController.h"
#include "Core/BurnItPlayerState.h"
#include "HUD/BurnItHUD.h"

// Sets default values
ABurnItCharacter::ABurnItCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Character doesnt have a device at start
	bHasDevice = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a LookAtSensor capsule
	LookAtSensor = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LookAtSensor"));
	LookAtSensor->SetupAttachment(FirstPersonCameraComponent);
	LookAtSensor->InitCapsuleSize(7.f, 125.f);
	LookAtSensor->SetRelativeLocation(FVector(90.f, 0.f, 0.f));
	LookAtSensor->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	LookAtSensor->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LookAtSensor->SetCollisionResponseToAllChannels(ECR_Overlap);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

// Called when the game starts or when spawned
void ABurnItCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABurnItCharacter::SetSprintSpeed()
{
	//GetMovementComponent()->GetMaxSpeed();
}

// Called every frame
void ABurnItCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
/*void ABurnItCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

void ABurnItCharacter::SetHasDevice(bool bNewHasDevice)
{
	bHasDevice = bNewHasDevice;
}

void ABurnItCharacter::SetIgnitionDevice(ABurnItIgnitionDevice* NewIgnitionDevice)
{
	IgnitionDevice = NewIgnitionDevice;
}

void ABurnItCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	SetInitialConfig();
}

void ABurnItCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	//SetInitialConfig();
}

void ABurnItCharacter::SetInitialConfig()
{
	ABurnItPlayerState* PS = GetPlayerState<ABurnItPlayerState>();
	check(PS);
	//PS->GetPlayerController()->GetHUD()
	
	//FlammableComponent = PS->GetFlammableComponent();

	// Initialize HUD
	/*if (ABurnItPlayerController* PC = Cast<ABurnItPlayerController>(GetController()))
	{
		if (ABurnItHUD* BurnItHUD = Cast<ABurnItHUD>(PC->GetHUD()))
		{
			BurnItHUD->InitOverlay();
		}
	}*/
	if (ABurnItHUD* HUD = Cast<ABurnItHUD>(Cast<ABurnItPlayerController>(Controller)->GetHUD()))
	{
		HUD->InitOverlay();
	}
}

