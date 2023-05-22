// 2023 Labverso, Brazil. Imersion Test.


#include "EnemyCharacterBase.h"
#include "Engine/World.h"
#include "LabTIMEImersionTest/Weapons/Base/WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharacterBase::AEnemyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Params;

	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	EnemyWeapon = GetWorld()->SpawnActor<
		AWeaponBase>(BP_Weapon_AssaultRifle, FTransform(), Params);

	EnemyWeapon->AttachToComponent(Cast<USceneComponent>(GetMesh()),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("Socket_Weapon"));

}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyCharacterBase::SetHealth(float Damage)
{
	/* Check if the Enemy still have Health */
	if (Health > 0.0f)
	{
		Health -= Damage;
	}

	/* Check if the Enemy took enough damage to be dead */
	else if (Health <= 0.0f)
	{
		/* A flag that indicates the enemy is dead */
		bIsDead = true;
	}
}

float AEnemyCharacterBase::GetHealth()
{
	return Health;
}
