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
#include "Camera/CameraComponent.h"

AWeaponBase::AWeaponBase()
{
	// Constructor.

	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(
		FName("MalhaDaArma"));
	RootComponent = WeaponMesh;

	WeaponArrow = CreateDefaultSubobject<UArrowComponent>(
		FName("Seta da Arma"));
	WeaponArrow->SetupAttachment(WeaponMesh);
	WeaponArrow->SetRelativeLocation(FVector(74.f, -1.f, 10.f));
	WeaponArrow->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));


	// Create the Aiming Camera Component.
	AimingCameraComponent = CreateDefaultSubobject<UCameraComponent>(
		TEXT("AimingCamera"));
	AimingCameraComponent->SetWorldScale3D(FVector(0.25f));
	
	AimingCameraComponent->bAutoActivate = false;
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// AimingCamera Setup Attachment it is done after weapon spawn.
	AimingCameraComponent->AttachToComponent(Cast<USceneComponent>
		(WeaponMesh), FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("Aiming_Socket"));

	// Set the current ammunition amount as we start the game with full ammo
	WeaponCurrentAmmunitionAmount = WeaponAmmunitionAmount;

	PlayerCharacter = Cast<AMainPlayerCharacter>(GetWorld()->
		GetFirstPlayerController()->GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found"));
	}

	CameraManager = Cast<APlayerCameraManager>(GetWorld()->
		GetFirstPlayerController()->PlayerCameraManager);
	if (!CameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Camera Manager not found"));
	}

	// Setup the Max Ammo for the weapon.
	WeaponMagazineMaxAmmo = WeaponAmmunitionAmount * WeaponMagazineAmount ;
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::FireWeapon()
{
	if (WeaponCurrentAmmunitionAmount > 0 && !bIsWeaponReloading)
	{
		// Make one shot.
		WeaponShot();
	}
	else
	{
		Reload();
	}
}

void AWeaponBase::StopFiringWeapon()
{
	WeaponSpreadCurrentValue = 0.0f;
}

void AWeaponBase::WeaponShot()
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
	//FVector FirePoint = WeaponArrow->GetComponentLocation();
	FVector FirePoint = CameraManager->GetCameraLocation();
	// Set Fire Direction, uses ArrowComponent as Reference.
	FVector Dir = CameraManager->GetCameraRotation().Vector();
	
	// ------ Spread Logic: -------
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream = RandomSeed;
	const float CurrentSpread = WeaponSpreadCurrentValue;
	const float SpreadCone = FMath::DegreesToRadians(
		WeaponSpreadCurrentValue * 0.5);
	const FVector ShootDir = WeaponRandomStream.VRandCone(Dir, SpreadCone,
		SpreadCone);
	// ------ End Spread Logic. ------
	
	// Handles the raycast behavior, lenght and range.
	FVector EndRaycastTrack = FirePoint + (ShootDir * WeaponMaxRange);
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
		return;
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

	// Spend one ammo after shot.
	WeaponCurrentAmmunitionAmount -= 1;
	UE_LOG(LogTemp, Warning, TEXT("Current Ammo: %d  Current Magazine: %d"),
		WeaponCurrentAmmunitionAmount, WeaponMagazineMaxAmmo);

	// Add SpreadValue for consecultive shots.
	WeaponSpreadCurrentValue += WeaponSpreadCoef;
	UE_LOG(LogTemp, Warning, TEXT("Weapon Spread: %f"), WeaponSpreadCurrentValue);
}

void AWeaponBase::WaitForReload()
{
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
	bIsWeaponReloading = false;
	PlayerCharacter->bIsReloadingWeapon = false;
}

void AWeaponBase::Reload()
{
	if (WeaponMagazineMaxAmmo > 0 && !bIsWeaponReloading)
	{
		bIsWeaponReloading = true;
		PlayerCharacter->bIsReloadingWeapon = true;

		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,
			&AWeaponBase::WaitForReload, ReloadTimeInterval, false);

		UE_LOG(LogTemp, Error, TEXT("RELOAD!"));

		PlayReloadWeaponSoundEFX(GetActorLocation());

		// The amount of bullets that will be reloaded.
		int32 ReloadedBullets = WeaponAmmunitionAmount -
			WeaponCurrentAmmunitionAmount;

		// Ensures that when the amount of ammunition left in the magazine
		// is less than needed for a full reload, only the remaining bullets
		// will be reloaded. 
		if (ReloadedBullets > WeaponMagazineMaxAmmo)
		{
			ReloadedBullets = WeaponMagazineMaxAmmo;
		}

		WeaponMagazineMaxAmmo -= ReloadedBullets;

		WeaponCurrentAmmunitionAmount += ReloadedBullets;
	}
	else if(!bIsWeaponReloading)
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of Ammo."));
		// Play ou of ammo sound efx.
		PlayOutOfAmmoSoundEFX(GetActorLocation());
	}
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
	const FVector Loc = WeaponArrow->GetComponentLocation();
	const FRotator Rot = WeaponArrow->GetComponentRotation();
	const FVector Scale = FVector(0.5f);

	// Spawn the MuzzleEFX.
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleEFX,
		Loc, Rot, Scale, true);
}

void AWeaponBase::PlayGunshotSoundEFX(FVector PlaySoundLocation)
{
	if (!ShotSFX)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not play ShotSFX, null reference"));
		return;
	}

	// Make this weapon loud - Uses sound system to spawn Shot Sound.
	UGameplayStatics::PlaySoundAtLocation(WeaponArrow,
		ShotSFX, PlaySoundLocation);
}

void AWeaponBase::PlayReloadWeaponSoundEFX(FVector PlaySoundLocation)
{
	if (!ReloadSFX)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("Could not play ReloadSFX, null reference"));
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(WeaponArrow,
		ReloadSFX, PlaySoundLocation);
}

void AWeaponBase::PlayOutOfAmmoSoundEFX(FVector PlaySoundLocation)
{
	if (!OutOfAmmoSFX)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not play OutOfAmmoSFX, null reference"));
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(WeaponArrow,
		OutOfAmmoSFX, PlaySoundLocation);
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
		if (Enemy->bIsDead == false)
		{
			// Damage the Enemy Health.
			Enemy->SetHealth(DamageOnEnemy);
		}
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



