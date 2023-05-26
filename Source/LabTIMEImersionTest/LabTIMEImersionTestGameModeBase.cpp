// Copyright Epic Games, Inc. All Rights Reserved.


#include "LabTIMEImersionTestGameModeBase.h"
#include "MainPlayer/MainPlayerController.h"
#include "MainPlayer/MainPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
//#include "Engine/EngineTypes.h"




ALabTIMEImersionTestGameModeBase::ALabTIMEImersionTestGameModeBase()
{
	// Indica qual será a classe padrão do DefaultPawn neste GameMode
	DefaultPawnClass = AMainPlayerCharacter::StaticClass();

	// Indica qual será a classe padrão do PlayerController neste GameMode
	PlayerControllerClass = AMainPlayerController::StaticClass();
}

void ALabTIMEImersionTestGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ShowPlayersHUD();
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
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find the Widget PlayerHUD"));
		return;
	}

	// Put the Player's Widget in the screen.
	CurrentWidget->AddToViewport();
}
