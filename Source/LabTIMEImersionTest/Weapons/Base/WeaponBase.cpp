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

	// PS: Não posso quebrar a linha do endereço da referencia do Construtor.
	// seria essa a exceção?
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

	if (WeaponArrow != nullptr)
	{
		// Set weapon ArrowComponent as FirePoint Origin.
		FVector FirePoint = WeaponArrow->GetComponentLocation();

		// Set Fire Direction, uses ArrowComponent as Reference.
		FVector Dir = WeaponArrow->GetComponentRotation().Vector();

		// Handles the raycast lenght and range.
		FVector EndRaycastTrack = FirePoint + (Dir * 8000.f);

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
		
		// Make this weapon loud - Uses sound system to spawn Shot Sound.
		if (ShotSFX)
		{
			UGameplayStatics::PlaySoundAtLocation(WeaponArrow,
				ShotSFX, FirePoint);
		}

		// Check if the ray hit something.
		if (HitSomething)
		{
			UE_LOG(LogTemp, Warning, TEXT("PEW! Hit Something!"));

			// Which Actor did raycast hit? This return the answer.
			AActor* HitActor = HitResultInfo.GetActor();

			// Check If the raycast hit an Actor with a SkeletalMesh type,
			// or subclass or suboject.
			if (HitActor->GetClass()->IsChildOf(
				ASkeletalMeshActor::StaticClass()) && HitBloodEFX)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
					HitBloodEFX, HitResultInfo.Location, 
					HitResultInfo.ImpactNormal.Rotation(), true);
			}
			// If not a SkeletalMesh type, then uses 
			// HitHardSurfaceEFX/HitDecalVFX.
			else if (HitHardSurfaceEFX)
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

		/*
		// Draw a visible ray, to see its working.
		DrawDebugLine(GetWorld(), FirePoint, EndRaycastTrack, FColor::Red,
			false, 5.0f, (uint8)0, 1.0f);
		*/

		// MuzzleEFX can be set by way of Blueprints.
		if (MuzzleEFX)
		{
			// Uses ArrowComponent as reference to spawn Muzzle Efx.
			FVector Loc = WeaponArrow->GetComponentLocation();
			FRotator Rot = WeaponArrow->GetComponentRotation();
			FVector Scale = FVector(0.5f);
			// Spawn the MuzzleEFX.
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleEFX,
				Loc, Rot, Scale, true);
		}
	}
	
}

