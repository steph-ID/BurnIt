// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BurnItPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/BurnItCharacter.h"
#include "Core/BurnItPlayerState.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ABurnItPlayerController::ABurnItPlayerController()
{
}

void ABurnItPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void ABurnItPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABurnItPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABurnItPlayerController::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABurnItPlayerController::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABurnItPlayerController::Look);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABurnItPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	/*ABurnItPlayerState* PS = GetPlayerState<ABurnItPlayerState>();
	if (PS)
	{
		Cast<ABurnItCharacter>(GetCharacter())->SetInitialConfig();
	}*/
}


void ABurnItPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (PossessedPawn != nullptr)
	{
		// add movement 
		PossessedPawn->AddMovementInput(PossessedPawn->GetActorForwardVector(), MovementVector.Y);
		PossessedPawn->AddMovementInput(PossessedPawn->GetActorRightVector(), MovementVector.X);
	}
}

void ABurnItPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (PossessedPawn != nullptr)
	{
		// add yaw and pitch input to controller
		PossessedPawn->AddControllerYawInput(LookAxisVector.X);
		PossessedPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABurnItPlayerController::Jump()
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void ABurnItPlayerController::StopJumping()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void ABurnItPlayerController::Crouch()
{
	if (!GetCharacter()->GetCharacterMovement()->IsMovingOnGround()) { return; }
	if (GetCharacter())
	{
		GetCharacter()->Crouch();
	}
}

void ABurnItPlayerController::UnCrouch()
{
	if (GetCharacter())
	{
		GetCharacter()->UnCrouch();
	}
}

void ABurnItPlayerController::Sprint()
{
}

void ABurnItPlayerController::StopSprint()
{
}
