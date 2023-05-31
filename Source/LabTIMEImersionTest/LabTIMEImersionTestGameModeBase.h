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

	UFUNCTION()
	void SetGameMode();

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
	//UPROPERTIES.

	/* 
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
	/* 
	* Handle's with player atributes informations, like health,
	* ammo/magazine and armor.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Health")
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	/** Handle's the current Widget on HUD */
	UPROPERTY()
	class UUserWidget* CurrentWidget = nullptr;

private:
	/** Handles the player current score */
	UPROPERTY()
		int32 Score;
};
