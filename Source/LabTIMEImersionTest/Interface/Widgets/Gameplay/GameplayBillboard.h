// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "Widget/UserWidgetBase.h"
#include "GameplayBillboard.generated.h"

/**
* This widget is used to show gameplay status on a billboard.
* Thus, this shows the score of the player (the number of enemis killed).
*/
UCLASS()
class LABTIMEIMERSIONTEST_API UGameplayBillboard : public UUserWidgetBase
{
	GENERATED_BODY()


public:

	virtual void NativeConstruct() override;

protected:

	bool Initialize() override;

private:

	UFUNCTION()
		FText SetScoreField();

private:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ScoreText;

};
