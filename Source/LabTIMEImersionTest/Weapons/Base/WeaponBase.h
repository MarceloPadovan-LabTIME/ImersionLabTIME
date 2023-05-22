// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

/** 
* This is the abstract base class for all weapons.
* It deals with the base functionality that all weapons have, 
* e.g., the base mesh, firing the weapon, weapon common properties, and etc.
* @note Every weapon should inherit this base class
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties */
	AWeaponBase();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Fires the weapon */
	virtual void FireWeapon();

public:
	/** Getter to the weapon's current ammunition amount */
	UFUNCTION(BlueprintCallable, 
		meta=(Tooltip="Getter to the weapon's current ammo"))
	int32 GetWeaponCurrentAmmo() { return WeaponAmmunitionAmount; }

	/** Getter to the weapon's name */
	UFUNCTION(BlueprintCallable, 
		meta = (Tooltip = "Getter to the weapon's name"))
	FString GetWeaponName() { return WeaponName; }

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:
	/** 
	* The weapon ammunition amount. 
	* The bullet rounds amount it can fire in a row 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, 
		meta=(Tooltip="The weapon ammunition amount", AllowPrivateAccess=True))
	int32 WeaponAmmunitionAmount = 0;

	/** The weapon's name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, 
		meta=(Tooltip="The weapon's name", AllowPrivateAccess=True))
	FString WeaponName = FString();

	/** The weapon`s mesh*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arma",
		meta = (AllowPrivateAcess = "true"))
	class USkeletalMeshComponent* MalhaDaArma;

	/* The weapon`s ArrowComponent(for fire origin and direction */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arma",
		meta = (AllowPrivateAcess = "true"))
	class UArrowComponent* WeaponArrow;

	/* The weapon`s Effects(EFX) - Muzzle Flash */
	UPROPERTY(EditAnywhere, Category = "ShotEFX")
	class UParticleSystem* MuzzleEFX;

	/* The weapon`s shot sound effect (SFX) */
	UPROPERTY(EditAnywhere, Category = "ShotEFX")
		class USoundBase* ShotSFX;

	/* The weapon`s Hit Effect, blood for organic, splash for other */
	UPROPERTY(EditAnywhere, Category = "HitEFX")
	class UParticleSystem* HitBloodEFX;
	UPROPERTY(EditAnywhere, Category = "HitEFX")
	class UParticleSystem* HitHardSurfaceEFX;

	/* The weapon`s Visual Hit Effect, decals for affected surface */
	UPROPERTY(EditAnywhere, Category = "HitEFX")
	class UMaterialInterface* HitDecalVFX;

protected:
	/** The amount of ammunition the weapon still has on it's chamber */
	int32 WeaponCurrentAmmunitionAmount = 0;
};
