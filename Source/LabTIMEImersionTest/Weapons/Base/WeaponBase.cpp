// 2023 Labverso, Brazil. Imersion Test.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/EngineTypes.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/SkeletalMeshActor.h"
#include "Materials/MaterialInterface.h"
#include "Math/UnrealMathUtility.h"
#include "Sound/SoundBase.h"
#include "GameFramework/Character.h"
#include "LabTIMEImersionTest/Enemies/Base/EnemyCharacterBase.h"
#include "LabTIMEImersionTest/MainPlayer/MainPlayerCharacter.h"

AWeaponBase::AWeaponBase()
{
	// Constructor.

	PrimaryActorTick.bCanEverTick = true;

	// IDK if is a good practice declarations in the Constructor Scope...
	// Feel free to change. xD

	// These declarations prevents Unreal from crashing.
	MuzzleEFX = nullptr;
	HitBloodEFX = nullptr;
	HitHardSurfaceEFX = nullptr;
	HitDecalVFX = nullptr;
	ShotSFX = nullptr;

	MalhaDaArma = CreateDefaultSubobject<USkeletalMeshComponent>(
		FName("MalhaDaArma"));
	RootComponent = MalhaDaArma;

	// TO DO:
	// Find a way to create multiple variants of weapon`s type,
	// and change your mesh.
	ConstructorHelpers::FObjectFinder<USkeletalMesh>Malha(TEXT
	("SkeletalMesh'/Game/Art/Meshes/Guns/SkeletalMeshes/SkeletalM_AK47.SkeletalM_AK47'"));

	if (Malha.Succeeded())
	{
		MalhaDaArma->SetSkeletalMesh(Malha.Object);
	}

	WeaponArrow = CreateDefaultSubobject<UArrowComponent>(
		FName("Seta da Arma"));
	WeaponArrow->SetupAttachment(MalhaDaArma);
	WeaponArrow->SetRelativeLocation(FVector(74.f, -1.f, 10.f));
	WeaponArrow->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// Set the current ammunition amount as we start the game with full ammo
	WeaponCurrentAmmunitionAmount = WeaponAmmunitionAmount;
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::FireWeapon()
{
	WeaponArrow = FindComponentByClass<UArrowComponent>();
	if (!WeaponArrow)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("Could not FireWeapon, WeaponArrow not found."));
		return;
	}

	// Create a shot raycast:
	// Set weapon ArrowComponent as FirePoint Origin.
	FVector FirePoint = WeaponArrow->GetComponentLocation();
	// Set Fire Direction, uses ArrowComponent as Reference.
	FVector Dir = WeaponArrow->GetComponentRotation().Vector();
	// Handles the raycast lenght and range.
	FVector EndRaycastTrack = FirePoint + (Dir * WeaponMaxRange);
	FHitResult HitResultInfo;

	FCollisionQueryParams Params;
	// Ensures that the raycast will not collide with the weapon`s Actor.
	// and his components.
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	Params.bTraceComplex = true;

	// Invoke Raycast by Unreal Default. ??? IDK what I`m saying,
	// this is the way
	// How to unreal use the raycast system.
	bool HitSomething = GetWorld()->LineTraceSingleByChannel(HitResultInfo,
		FirePoint, EndRaycastTrack, ECollisionChannel::ECC_Visibility,
		Params);

	PlayGunshotSoundEFX(FirePoint);

	if (!HitSomething)
	{
		// Debugging: Check if the ray hit something.
		UE_LOG(LogTemp, Warning, 
			TEXT("PEW! The shot was fired, but it didn`t hit anything."));
	}

	// Debugging: Check if the ray hit something.
	UE_LOG(LogTemp, Warning, TEXT("PEW! Hit Something!"));

	// Which Actor did raycast hit? This return the answer.
	AActor* HitActor = HitResultInfo.GetActor();

	// Check If the raycast hit an Actor of class type ACharacter,
	// or subclass or suboject.
	if (HitActor->GetClass()->IsChildOf(
		ACharacter::StaticClass()) && HitBloodEFX)
	{
		HitOrganicTargets(HitResultInfo, HitActor);
	}
	else
	{
		HitAHardSurface(HitResultInfo);
	}

	SpawnMuzzleEFX();

}

void AWeaponBase::SpawnMuzzleEFX()
{
	// MuzzleEFX can be set by way of Blueprints.
	if (!MuzzleEFX)
	{
		UE_LOG(LogTemp, Error, TEXT("Can`t Spawn the Muzzle Effect."));
		return;
	}

	// Uses ArrowComponent as reference to spawn Muzzle Efx.
	FVector Loc = WeaponArrow->GetComponentLocation();
	FRotator Rot = WeaponArrow->GetComponentRotation();
	FVector Scale = FVector(0.5f);

	// Spawn the MuzzleEFX.
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleEFX,
		Loc, Rot, Scale, true);
}

void AWeaponBase::PlayGunshotSoundEFX(FVector PlaySoundLocation)
{
	// Make this weapon loud - Uses sound system to spawn Shot Sound.
	if (ShotSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(WeaponArrow,
			ShotSFX, PlaySoundLocation);
	}
}

void AWeaponBase::HitOrganicTargets(FHitResult HitResultInfo, AActor* HitActor)
{
	// Hit and Spawn HitBlood Effect at the Hit location.
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		HitBloodEFX, HitResultInfo.Location,
		HitResultInfo.ImpactNormal.Rotation(), true);

	// Make a cast to test if the raycast hit a PlayerCharacter.
	// If the hitResult return a PlayerCharacter(Player),
	// hit and cause some Damage
	AMainPlayerCharacter* Player = Cast<AMainPlayerCharacter>(HitActor);
	if (Player != nullptr)
	{
		// Player take some Damage.
		Player->SetHealth(DamageOnPlayer);
	}

	// Try another cast to check if the raycast hit an Enemy,
	// If the Hitresult return a EnemyCharacter(Enemy),
	// hit and cause some Damage.
	AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(HitActor);
	if (Enemy != nullptr)
	{
		// Damage the Enemy Health.
		Enemy->SetHealth(DamageOnEnemy);
	}
}

void AWeaponBase::HitAHardSurface(FHitResult HitResultInfo)
{
	// If not a ACharacter type, then uses 
	// HitHardSurfaceEFX/HitDecalVFX.
	if (HitHardSurfaceEFX)
	{
		// Spawn Hit EFX.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			HitHardSurfaceEFX, HitResultInfo.Location,
			HitResultInfo.ImpactNormal.Rotation(), true);

		// For cool EFX. Radomize the size of decals.
		FVector RandomSize = FVector(FMath::RandRange(10.f, 50.f));

		// Spawn Hit Decal VFX.
		UGameplayStatics::SpawnDecalAttached(HitDecalVFX, RandomSize,
			HitResultInfo.GetComponent(), NAME_None,
			HitResultInfo.Location,
			HitResultInfo.ImpactNormal.Rotation(),
			EAttachLocation::KeepWorldPosition, 60.f);
	}
}

