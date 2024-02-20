// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BurnItGameStateBase.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	None		UMETA(DisplayName = "None"),
	Waiting		UMETA(DisplayName = "Waiting"),
	Playing		UMETA(DisplayName = "Playing"),
	Ending		UMETA(DisplayName = "Ending"),
	Results		UMETA(DisplayName = "Results"),
	GameOver	UMETA(DisplayName = "GameOver"),
};

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedDelegate, EGameState, NewGameState);

UCLASS()
class BURNIT_API ABurnItGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	// How long we should wait to start the game
	UPROPERTY(EditAnywhere)
	float GameStartCountdownDuration = 5.f;

	// Countdown time until round start
	UPROPERTY()
	float GameStartWaitTimer = 0.f;

	// Player's total 'match' time in seconds
	UPROPERTY()
	float GameplayTimer = 0.f;

	// Level to load after the game ends
	UPROPERTY(EditAnywhere)
	ULevel* PostGameLevel = nullptr;

	EGameState GameState = EGameState::None;
	
	//UPROPERTY()
	//ABurnItPlayerController* PlayerController = nullptr;

public:
	ABurnItGameStateBase();

	// Calls functions to start a game round
	UFUNCTION(BlueprintCallable)
	void PrepGameRound();

	// Beings gameplay
	UFUNCTION(BlueprintCallable)
	void StartGameRound();

	// Calls functions to start a Free Roam round
	UFUNCTION(BlueprintCallable)
	void StartFreeRoamRound();
	
	UFUNCTION(BlueprintCallable)
	void LeaveRound();
	
	UFUNCTION(BlueprintCallable)
	void FuelDepleted();
	
	UFUNCTION(BlueprintCallable)
	void PlayerDied();
	
	//UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Game State")
	//FGameStart GameStart;
	
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Game State")
	FOnGameStateChangedDelegate OnGameStateChange;
	
	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const { return GameState; }
	
	UFUNCTION(BlueprintCallable)
	float GetGameStartWaitTimer() const { return GameStartWaitTimer; }
	
	UFUNCTION(BlueprintCallable)
	float GetGameplayTimer() const { return GameplayTimer; }

private:

	FTimerHandle GameCountdownTimerHandle;

	// Tracks time spent playing the round
	UFUNCTION()
	void SetGameplayTime(float DeltaSeconds);

	// Countdown timer to being the game after loading the level
	UFUNCTION()
	void StartGameCountdown(float DeltaSeconds);

	virtual void Tick(float DeltaSeconds) override;
};
