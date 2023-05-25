// 2023 Labverso, Brazil. Imersion Test.


#include "MainPlayerController.h"
#include "LabTIMEImersionTest/Interface/MainHUD.h"
#include "DrawDebugHelpers.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind the player "OpenScoreboard" input to show the scoreboard widget
	InputComponent->BindAction("OpenScoreboard", IE_Pressed, 
		this, &AMainPlayerController::RequestOpenScoreBoard);
	InputComponent->BindAction("OpenScoreboard", IE_Released, 
		this, &AMainPlayerController::RequestCloseScoreBoard);
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainPlayerController::RequestOpenScoreBoard()
{
	AMainHUD* PlayerMainHUD = Cast<AMainHUD>(GetHUD());
	if (!PlayerMainHUD)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("Could not get main HUD to show scoreboard."));
		return;
	}

	// Request the main HUD to show the scoreboard widget
	PlayerMainHUD->ToggleScoreboardWidget(true);
}

void AMainPlayerController::RequestCloseScoreBoard()
{
	AMainHUD* PlayerMainHUD = Cast<AMainHUD>(GetHUD());
	if (!PlayerMainHUD)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("Could not get main HUD to show scoreboard."));
		return;
	}

	// Request the main HUD to show the scoreboard widget
	PlayerMainHUD->ToggleScoreboardWidget(false);
}
