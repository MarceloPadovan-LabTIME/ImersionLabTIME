// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"

/**
* This class is used to save GameModes informations, like rules,
* difficulty params, persistent data, and others.
*/
class LABTIMEIMERSIONTEST_API MyGameModeSettings
{
public:
	

public:
	//UFUNCTIONS.

public:
	//UPROPERTIES.

	/**
	* If true : The rules of the current game mode will be set by time,
	* that is, there will be a countdown(30s/60s/90s) that the player will
	* have to eliminate as many enemies as possible. 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModes")
	bool bIsGameModeByTime = false;

	/** 
	* A array of GameModeByTime options,
	* the respective countdowns values : 30, 60, 90 seconds.
	* this value represents the duration of the game.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModes")
	int GameModeByTimeOptions[3] = {30,60,90};

	/** Index for Selected GameMode By Time Option, 0 = 30, 1 = 60, 2 = 90. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModes")
	int SelectedTimeOption;

	/** 
	* If true: The rules of the current game mode will be by count of kills,
	* there will be no time stamp, and the player must eliminate the chosen
	* amount of enemies(30/60/90).
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModes")
	bool bIsGameModeByKills = false;

	/** 
	* If true: Enable enemies to have armor values, meaning the amount of
	* damage they take will be reduced. 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehavior")
	bool bAllowArmor = false;

	/** 
	* If true: Enable enemies to move and fire at the player.
	* This option increases the difficulty of the game.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehavior")
	bool bAllowMovement = false;

	/**
	* If true: Enable enemies to respawn and come back to the game endlessly.
	* This option increases the difficulty of the game.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehavior")
	bool bAllowRespawn = false;

};
