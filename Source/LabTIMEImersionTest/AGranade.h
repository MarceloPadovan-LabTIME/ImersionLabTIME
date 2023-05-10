// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGranade.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AAGranade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAGranade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Visual")
	class UStaticMeshComponent* MalhaDoAtor;

	UPROPERTY(EditAnywhere, Category = "Visual")
	class USphereComponent* ColisorDoAtor;

};
