// Copyright Epic Games, Inc. All Rights Reserved.


#include "LabTIMEImersionTestGameModeBase.h"
#include "MainPlayer/MainPlayerController.h"
#include "MainPlayer/MainPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Engine/EngineTypes.h"
#include "MyGameModeSettings.h"
#include "LabTIMEImersionTest/MyGameModeSettings.h"
#include "Components/TextBlock.h"
//#include "LabTIMEImersionTest/MainPlayer/MainPlayerCharacter.h"




ALabTIMEImersionTestGameModeBase::ALabTIMEImersionTestGameModeBase()
{
	// Indicates what will be the default DefaultPawn class in this GameMode.
	DefaultPawnClass = AMainPlayerCharacter::StaticClass();

	// Indicates what will be the default PlayerController class 
	// in this GameMode.
	PlayerControllerClass = AMainPlayerController::StaticClass();
}

void ALabTIMEImersionTestGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ShowPlayersHUD();

	// Instance and Inicialization of a MyGameModeSettings pointer reference.
	GameModeSettings = new MyGameModeSettings();

	// Instance and inicialization of MainPlayerCharacater ptr, get the player
	// characater in the world.
	//MainPlayerCharacter = Cast<AMainPlayerCharacter>
	//	(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Set the initial value of player's score.
	Score = 0;
}

void ALabTIMEImersionTestGameModeBase::ShowPlayersHUD()
{
	// Get the player's character in the world.
	AMainPlayerCharacter* Player = Cast<AMainPlayerCharacter>
		(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Set the CurrentWidget with player's Widget, which deals with player
	// attributes such as health, ammo and amor.
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

	if (!CurrentWidget)
	{
		// Debug.
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find the Widget PlayerHUD"));
		return;
	}

	// Put the Player's Widget in the screen.
	CurrentWidget->AddToViewport();
}

void ALabTIMEImersionTestGameModeBase::ResetLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Map_LabTIMEImersion");
}

void ALabTIMEImersionTestGameModeBase::CountdownTimer()
{
	TimerCount--;

	// Stop the Countdown when the value reaches 0.
	if (TimerCount == 0)
	{
		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);

		ResetLevel();
	}
}

// PS: Remember to call this function in BeginPlay when ready.
void ALabTIMEImersionTestGameModeBase::SetGameMode()
{
	if (GameModeSettings->bIsGameModeByTime)
	{
		// Ensures that the GameMode ByKills will not be true.
		GameModeSettings->bIsGameModeByKills = false;

		// Call the function who will apply the game mode rules.
		SetGameModeByTime();
	}
	else if (GameModeSettings->bIsGameModeByKills)
	{
		// Ensures that the GameModeByTime will not be true.
		GameModeSettings->bIsGameModeByTime = false;
	}
}

void ALabTIMEImersionTestGameModeBase::SetGameModeByTime()
{
	// Applies selected value to time options
	TimerCount = GameModeSettings->
		GameModeByTimeOptions[GameModeSettings->SelectedTimeOption];

	// Triggers the game countdown.
	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this,
		&ALabTIMEImersionTestGameModeBase::CountdownTimer, 1.0f, true, 1.0f);
}

void ALabTIMEImersionTestGameModeBase::SetEnemyBehavior()
{
	//TO DO.
	//Allow Movement.
	//Allow Armor.
}

void ALabTIMEImersionTestGameModeBase::SetScorePoints(int32 value)
{
	Score += value;
}

int32 ALabTIMEImersionTestGameModeBase::GetScorePoints()
{
	return Score;
}
