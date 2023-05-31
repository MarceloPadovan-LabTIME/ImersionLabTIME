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

	GetWorld()->GetTimerManager().SetTimer(NewEnemySpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnEnemyTime, true, SpawnEnemyTime);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::SpawnEnemy()
{
	SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
		GetActorLocation(), SpawnAreaVolume->GetScaledBoxExtent());

	FRotator SpawnRot = GetActorRotation();

	GetWorld()->SpawnActor<AEnemyCharacterBase>(BP_EnemyCharacter,
		SpawnLocation, SpawnRot);
}

