// 2023 Labverso, Brazil. Imersion Test.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MalhaDaArma = CreateDefaultSubobject<USkeletalMeshComponent>(
		FName("Malha Da Arma"));
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
	UE_LOG(LogTemp, Warning, TEXT("PEW"));
}

