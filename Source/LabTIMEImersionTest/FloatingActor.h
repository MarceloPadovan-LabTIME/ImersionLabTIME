// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Atributos")
	bool bIsTarget = false;

	UPROPERTY(EditAnywhere, Category = "Atributos")
	float MinRotation;
	UPROPERTY(EditAnywhere, Category = "Atributos")
	float MaxRotation;

	UPROPERTY(EditAnywhere, Category = "Atributos")
	float MinPosition;
	UPROPERTY(EditAnywhere, Category = "Atributos")
	float MaxPosition;

	UPROPERTY(EditAnywhere, Category = "Atributos")
	float MinScale;
	UPROPERTY(EditAnywhere, Category = "Atributos")
	float MaxScale;

private:
	float executionTime;
	float deltaHeight;
	FVector newLocation;
};
