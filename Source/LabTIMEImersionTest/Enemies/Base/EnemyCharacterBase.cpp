// 2023 Labverso, Brazil. Imersion Test.


#include "EnemyCharacterBase.h"

// Sets default values
AEnemyCharacterBase::AEnemyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
