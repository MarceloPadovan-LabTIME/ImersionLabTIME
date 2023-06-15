// 2023 Labverso, Brazil. Imersion Test.


#include "EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "LabTIMEImersionTest/Enemies/Base/EnemyCharacterBase.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to
	// improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(
		TEXT("DefaultSceneRoot"));
	SpawnAreaVolume = CreateDefaultSubobject<UBoxComponent>(
		TEXT("SpawnAreaVolume"));
	SpawnAreaVolume->AttachToComponent(RootComponent,
		FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	// Spawn a Enemy after initial wait time(first SpawnEnemyTime), and repeat
	// the function call SpawnEnemy() after seconds(second SpawnEnemyTime).
	// TODO: Maybe create a variable for the initialWaitTime.
	GetWorld()->GetTimerManager().SetTimer(NewEnemySpawnTimerHandle, this,
		&AEnemySpawner::SpawnEnemy, SpawnEnemyTime, true, SpawnEnemyTime);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::SpawnEnemy()
{
	// Chose a random location inside SpawnAreaVolume.
	SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
		GetActorLocation(), SpawnAreaVolume->GetScaledBoxExtent());

	// Randomize the Y(Yaw) rotation for SpawnEnemy.
	const float RandomYRotation = FMath::RandRange(0.0f, 360.0f);
	const FRotator RngSpawnRot = FRotator(0, RandomYRotation, 0);

	// A Parameter to esnures the enemies will not spawn inside of 
	// scene obstacles.
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// It actually spawns the enemy.
	GetWorld()->SpawnActor<AEnemyCharacterBase>(BP_EnemyCharacter,
		SpawnLocation, RngSpawnRot, Params);
}

