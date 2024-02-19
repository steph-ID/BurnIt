// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurnItGameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "BurnItGameStateBase.generated.h"

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
	float GameCountdownDuration = 5.f;

	// Player's total 'match' time in seconds
	UPROPERTY()
	float GameplayTimer;

	// Level to load after the game ends
	UPROPERTY(EditAnywhere)
	ULevel* PostGameLevel;

	EGameState GameState = EGameState::None;
	
	//UPROPERTY()
	//ABurnItPlayerController* PlayerController = nullptr;

public:

	// Calls functions to start the game
	UFUNCTION(BlueprintCallable)
	void PrepGame();

	// Calls functions to start the game
	UFUNCTION(BlueprintCallable)
	void StartGame();
	
	UFUNCTION(BlueprintCallable)
	void EndGame();
	
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

private:

	FTimerHandle GameCountdownTimerHandle;

	// Tracks time spent playing the round
	UFUNCTION()
	void SetGameplayTime();
	
	UFUNCTION()
	void StopGameplayTimer();

	// Countdown timer to being the game after loading the level
	UFUNCTION()
	void StartGameCountdown(float Seconds);
};
