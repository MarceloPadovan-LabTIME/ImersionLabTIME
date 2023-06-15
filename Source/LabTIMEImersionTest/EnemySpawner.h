// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties */
	AEnemySpawner();

public:
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

public:
	/** Will Spawn the Enemy BP in a pre-determinate area */
	UFUNCTION()
	void SpawnEnemy();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:
	/** Handles the EnemySpawn Area */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	class UBoxComponent* SpawnAreaVolume = nullptr;

	/** Position to Spawn the Enemy*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FVector SpawnLocation = FVector();

	/** The time in seconds to wait for new enemies to spawn  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SpawnEnemyTime = 5.0f;

	/** A reference of the Enemy type to spawn */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AEnemyCharacterBase> BP_EnemyCharacter;

protected:
	/** The Timer Handle for the New Enemies Spawn */
	FTimerHandle NewEnemySpawnTimerHandle;
};
