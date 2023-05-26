// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
};
