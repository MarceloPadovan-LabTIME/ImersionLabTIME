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

	// Gives a Weapon to the Enemy. Otherwise is not a fair play.
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
	// Check if the Enemy still have Health.
	if (Health > 0.0f)
	{
		Health -= Damage;
	}

	// Check if the Enemy took enough damage to be dead.
	else if (Health <= 0.0f)
	{
		// A flag that indicates the enemy is dead.
		bIsDead = true;
		// A delay to destroy the enemy actor, removing it from the level
		SetLifeSpan(5.0f);
		// removing the enemy weapon from the level too.
		EnemyWeapon->Destroy();
	}
}

float AEnemyCharacterBase::GetHealth()
{
	return Health;
}

bool AEnemyCharacterBase::bIsThisCharacterDead()
{
	return bIsDead;
}
