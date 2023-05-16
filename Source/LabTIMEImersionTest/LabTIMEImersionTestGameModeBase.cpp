// Copyright Epic Games, Inc. All Rights Reserved.


#include "LabTIMEImersionTestGameModeBase.h"
#include "MainPlayer/MainPlayerController.h"
#include "MainPlayer/MainPlayerCharacter.h"




ALabTIMEImersionTestGameModeBase::ALabTIMEImersionTestGameModeBase()
{
	// Indica qual ser� a classe padr�o do DefaultPawn neste GameMode
	DefaultPawnClass = AMainPlayerCharacter::StaticClass();

	// Indica qual ser� a classe padr�o do PlayerController neste GameMode
	PlayerControllerClass = AMainPlayerController::StaticClass();
}