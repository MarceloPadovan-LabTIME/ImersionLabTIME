// Copyright Epic Games, Inc. All Rights Reserved.


#include "LabTIMEImersionTestGameModeBase.h"
#include "MainPlayer/MainPlayerController.h"
#include "MainPlayer/MainPlayerCharacter.h"




ALabTIMEImersionTestGameModeBase::ALabTIMEImersionTestGameModeBase()
{
	// Indica qual será a classe padrão do DefaultPawn neste GameMode
	DefaultPawnClass = AMainPlayerCharacter::StaticClass();

	// Indica qual será a classe padrão do PlayerController neste GameMode
	PlayerControllerClass = AMainPlayerController::StaticClass();
}