// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
* The player's main player controller.
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:


public:
	/** Setup the player controller inputs */
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

private:
	/** Request the main HUD to open the scoreboard widget */
	void RequestOpenScoreBoard();

	/** Request the main HUD to close the scoreboard widget */
	void RequestCloseScoreBoard();
};
