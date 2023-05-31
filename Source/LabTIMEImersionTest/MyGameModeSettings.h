// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LABTIMEIMERSIONTEST_API MyGameModeSettings
{
public:
	MyGameModeSettings();
	~MyGameModeSettings();

public:
	//UFUNCTIONS.

public:
	//UPROPERTIES.

	/*
	* If true : The rules of the current game mode will be set by time,
	* that is, there will be a countdown(30s/60s) that the player will have to
	* eliminate as many enemies as possible. 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModes")
		bool bIsGameModeByTime = false;

	/** 
	* If true: The rules of the current game mode will be by count of kills,
	* there will be no time stamp, and the player must eliminate the chosen
	* amount of enemies(30/60/90).
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModes")
		bool bIsGameModeByKills = false;

	/* 
	* If true: Enable enemies to have armor values, meaning the amount of
	* damage they take will be reduced. 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehavior")
		bool bAllowArmor = false;

	/* 
	* If true: Enable enemies to move and fire at the player.
	* This option increases the difficulty of the game.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBehavior")
		bool bAllowMovement = false;

};
