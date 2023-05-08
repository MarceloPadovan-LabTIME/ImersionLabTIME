// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

/**
* This is the player main player state.
* This player state will keep track of the player's score on the game.
* Thus, at this moment stores the amount of enemies we has killed.
* This class can be accessed to show the player score on the screen, 
* for instance.
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	/** 
	* Getter to the enemies killed amount. The amount of enemies 
	* killed by the player.
	* 
	* @return The amount of enemies the player has killed since last reset
	*/
	UFUNCTION(BlueprintCallable, 
		meta=(Tooltip="Get the amount of enemies killed by the player"))
	int32 GetEnemiesKilledAmount() { return EnemiesKilledAmount; }

private:
	/** The amount of enemies killed by the player on the current round. */
	int32 EnemiesKilledAmount = 0;
};
