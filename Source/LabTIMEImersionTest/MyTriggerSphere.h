// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "MyTriggerSphere.generated.h"

/**
 * 
 */
UCLASS()
class LABTIMEIMERSIONTEST_API AMyTriggerSphere : public ATriggerSphere
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;


private:

	// me -> Eu mesmo.  other -> quem colidiu comigo.
	UFUNCTION()
	void ColisaoDetectada(AActor* me, AActor* other);

	UFUNCTION()
	void FimColisao(AActor* me, AActor* other);
		
	
};
