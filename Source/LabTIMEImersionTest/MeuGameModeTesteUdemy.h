// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MeuGameModeTesteUdemy.generated.h"

/**
 * 
 */
UCLASS()
class LABTIMEIMERSIONTEST_API AMeuGameModeTesteUdemy : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void StartPlay() override;
};
