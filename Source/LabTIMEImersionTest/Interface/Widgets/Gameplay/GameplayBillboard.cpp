// 2023 Labverso, Brazil. Imersion Test.


#include "GameplayBillboard.h"
#include "LabTIMEImersionTest/LabTIMEImersionTestGameModeBase.h"
#include "Components/TextBlock.h"

void UGameplayBillboard::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UGameplayBillboard::Initialize()
{
	bool Success = Super::Initialize();

	if(!Success)
	{
		return false;
	}

	if (!ScoreText)
	{
		UE_LOG(LogTemp, Error, TEXT("Score text not found."));
		return false;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World not found."));
		return false;
	}

	ALabTIMEImersionTestGameModeBase* MainGameMode =
		Cast<ALabTIMEImersionTestGameModeBase>(World->GetAuthGameMode());
	
	if (!MainGameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("Game Mode not found."));
		return false;
	}

	ScoreText->SetText(FText::FromString("Game mode set"));

	ScoreText->TextDelegate.BindUFunction(this, "SetScoreField");

	return true;
}

FText UGameplayBillboard::SetScoreField()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World not found."));
		return FText::FromString("Null");
	}

	ALabTIMEImersionTestGameModeBase* MainGameMode =
		Cast<ALabTIMEImersionTestGameModeBase>(World->GetAuthGameMode());

	if (MainGameMode)
	{
		return FText::FromString(FString::FromInt(MainGameMode->
			GetScorePoints()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Mode not found."));
		return FText::FromString("Null");
	}
	
	return FText::FromString("Null");
}
