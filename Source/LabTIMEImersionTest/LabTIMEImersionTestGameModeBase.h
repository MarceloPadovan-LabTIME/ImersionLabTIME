// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeSettings.h"
#include "LabTIMEImersionTestGameModeBase.generated.h"


/**
 * 
 */

UCLASS()
class LABTIMEIMERSIONTEST_API ALabTIMEImersionTestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	// Constructor.
	ALabTIMEImersionTestGameModeBase();

public:
	//UFUNCTIONS.

	/** Checks which game mode was chosen and calls its respective function. */
	UFUNCTION()
	void SetGameMode();

	/** Apply the time game mode chosen by the user. */
	UFUNCTION()
	void SetGameModeByTime();


	UFUNCTION()
	void SetGameModeOptions();

	UFUNCTION()
	void SetEnemyBehavior();


	/** Handles the changes in the player's score */
	UFUNCTION()
	void SetScorePoints(int32 value);

	/** Return the current score of the player */
	UFUNCTION()
	int32 GetScorePoints();

public:
	/** Reset the current level scene. */
	void ResetLevel();

public:
	//UPROPERTIES.

	/** Handle the countdown timer value , receive from GameMode By Time */
	UPROPERTY(BlueprintReadWrite)
	int TimerCount = 30;

public:

	/** 
	* This is a class created to handle the diferrents types os variables
	* using to setting the game modes.
	* Here a pointer to serve as reference, and allocate values in memory.
	*/
	class MyGameModeSettings* GameModeSettings = nullptr;

protected:
	virtual void BeginPlay() override;

	/* 
	* Assign the CurrentWidget on screen with Player's Widget (which deals with
	* player attributes such as health, ammo/magazine and amor).
	* To be parte of the HUD .
	*/
	void ShowPlayersHUD();

protected:
	//UPROPERTIES.

	/* 
	* Handle with player atributes informations, like health,
	* ammo/magazine and armor.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player HUD")
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	/** Handle the current Widget on HUD */
	UPROPERTY()
	class UUserWidget* CurrentWidget = nullptr;

private:
	/** Countdown the time value, until reaches 0. */
	void CountdownTimer();

private:
	/** The game countdown timer handle, when it reaches 0 the player loses. */
	FTimerHandle CountDownTimerHandle;

private:
	/** Handles the player current score */
	UPROPERTY()
	int32 Score;
};
