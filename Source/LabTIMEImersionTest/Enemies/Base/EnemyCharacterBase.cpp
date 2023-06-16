// 2023 Labverso, Brazil. Imersion Test.


#include "EnemyCharacterBase.h"
#include "Engine/World.h"
#include "LabTIMEImersionTest/Weapons/Base/WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LabTIMEImersionTest/EnemySpawner.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "LabTIMEImersionTest/LabTIMEImersionTestGameModeBase.h"
#include "LabTIMEImersionTest/MyGameModeSettings.h"

// Sets default values
// CONSTRUCTOR:
AEnemyCharacterBase::AEnemyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GetAWeapon();
	PlaySpawnEFX();

	LoadEnemyBehaviorParams();
}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyCharacterBase::LoadEnemyBehaviorParams()
{
	// Uncoment this after the GameMode change is ready.
	/*
	if(bAllowArmor)
	{
	Armor = 50.f;
	}
	*/
}

void AEnemyCharacterBase::GetAWeapon()
{
	// Gives a Weapon to the Enemy. Otherwise is not a fair play.

	// Create a parameter which will ensure that where will be no
	// collision conflicts
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn this character's(Enemy) weapon.
	EnemyWeapon = GetWorld()->SpawnActor<
		AWeaponBase>(BP_Weapon_AssaultRifle, FTransform(), Params);

	// Attach the weapon to the character hand socket, previously created.
	EnemyWeapon->AttachToComponent(Cast<USceneComponent>(GetMesh()),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("Socket_Weapon"));
}

void AEnemyCharacterBase::SetHealth(float Damage)
{
	// Uncoment this after GameModes is ready to use.
	/*
	if(bAllowArmor)
	{
		Damage = Damage * (1 - ArmorEffectiveness);
		Armor -= Damage;

		if(Armor <= 0.0f)
		{
			Armor = 0.f;
			Damage = Damage * 4;
		}
	}
    */

	// Check if the Enemy still have Health.
	if (Health > 0.0f && Armor <= 0.0f)
	{
		Health -= Damage;
	}

	// Check if the Enemy took enough damage to be dead.
	else if (Health <= 0.0f)
	{
		Health = 0.0f;
		Die();
	}
}

float AEnemyCharacterBase::GetHealth()
{
	return Health;
}

bool AEnemyCharacterBase::IsCharacterDead()
{
	return bIsDead;
}

void AEnemyCharacterBase::Die()
{
	AddPlayerScore();

	// A flag that indicates the enemy is dead.
	bIsDead = true;
	
	// Uncomment this after GameModes is ready to use.
	//if(bAllowRespawn)
	// {
	//		//Add respawn TimerManager here.
	// }
	
	// Uses a TimerManager to Respawn the Enemy after 5 seconds.
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this,
		&AEnemyCharacterBase::Respawn, 5.f, false);
	
	// Debug.
	UE_LOG(LogTemp, Warning, TEXT("Enemy Died"));
}

void AEnemyCharacterBase::Respawn()
{
	// Debug.
	UE_LOG(LogTemp, Warning, TEXT("Enemy Respawned"));

	// Give back the life state to this character.
	bIsDead = false;
	Health = 100.0f;
	RespawnLocation = FVector(440, -350, 220);
	SetActorLocation(RespawnLocation);
	PlaySpawnEFX();
}

void AEnemyCharacterBase::PlaySpawnEFX()
{
	// Spawn Parameters
	FVector SpawnLoc = GetActorLocation();
	FRotator SpawnRot = GetActorRotation();
	FVector Scale = FVector(1.0f);

	// Spawn the Enemy with a Spawn EFX.
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnEFX,
		SpawnLoc, SpawnRot, Scale, true);

}

void AEnemyCharacterBase::AddPlayerScore()
{
	MainGameMode = Cast<ALabTIMEImersionTestGameModeBase>(
		UGameplayStatics::GetGameMode(GetWorld()));

	MainGameMode->SetScorePoints(EnemyRewardScore);
}
