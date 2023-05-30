// 2023 Labverso, Brazil. Imersion Test.


#include "EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "LabTIMEImersionTest/Enemies/Base/EnemyCharacterBase.h"


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

void AEnemySpawner::SpawnEnemy()
{
	FVector SpawnLoc = GetActorLocation();
	FRotator SpawnRot = GetActorRotation();

	GetWorld()->SpawnActor<AEnemyCharacterBase>(BP_EnemyCharacter,
		SpawnLoc, SpawnRot);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	//SpawnEnemy();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

