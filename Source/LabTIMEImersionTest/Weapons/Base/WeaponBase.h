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

	/** Stop fires the weapon */
	virtual void StopFiringWeapon();

	/** Handle the single shot execution of an weapon */
	void WeaponShot();

	/** Handle the Reload Action of an weapon */
	void Reload();

public:
	/** Getter to the weapon's current ammunition amount */
	UFUNCTION(BlueprintCallable, 
		meta=(Tooltip="Getter to the weapon's current ammo"))
	int32 GetWeaponCurrentAmmo() { return WeaponAmmunitionAmount; }

	/** Getter to the weapon's name */
	UFUNCTION(BlueprintCallable, 
		meta = (Tooltip = "Getter to the weapon's name"))
	FString GetWeaponName() { return WeaponName; }

public:
	/** Reference:Player Character to use his public variables and functions */
	class AMainPlayerCharacter* PlayerCharacter;

public:
	/** First person aiming down sight camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* AimingCameraComponent = nullptr;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:
	/** Spawn a Muzzle Effect when a shot is taken */
	void SpawnMuzzleEFX();

	/** Every time a shot is made, this function will play the shot sound */
	void PlayGunshotSoundEFX(FVector PlaySoundLocation);

	/** Every time a reload is made, this function will play the reload sound */
	void PlayReloadWeaponSoundEFX(FVector PlaySoundLocation);
	
	/** Every time a shot is made with no ammo, this function will play the
	out of ammo sound */
	void PlayOutOfAmmoSoundEFX(FVector PlaySoundLocation);

	/** 
	* When the shot hit a organic body, this function will spawn a
	* BloodySplashHitEffect and identifies what kind of target hit, 
	* then inflict some damage to the target.
	*/
	void HitOrganicTargets(FHitResult HitResultInfo, AActor* HitActor);

	/** 
	* When the shot hit a hard surface instead of organic body,
	* this function will spawn a Hit Effect and a Decal with random size 
	*/
	void HitAHardSurface(FHitResult HitResultInfo);

	/** Handle the weapon's spread property */
	//void WeaponSpread();

	/** Delegate Function, the Weapon need to wait for the reload time to shot
	again */
    void WaitForReload();

protected:
	/** Ref: Acess the CameraManager to get the CameraViewport */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arma")
	class APlayerCameraManager* CameraManager = nullptr;

	/** The weapon's name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, 
		meta=(Tooltip="The weapon's name", AllowPrivateAccess=True))
	FString WeaponName = FString();

	/** The weapon`s mesh*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arma",
		meta = (AllowPrivateAcess = "true"))
	class USkeletalMeshComponent* MalhaDaArma;

	/** The weapon`s ArrowComponent(for fire origin and direction) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arma",
		meta = (AllowPrivateAcess = "true"))
	class UArrowComponent* WeaponArrow;

	/** The weapon`s Effects(EFX) - Muzzle Flash */
	UPROPERTY(EditAnywhere, Category = "ShotEFX")
	class UParticleSystem* MuzzleEFX;

	/** The weapon`s shot sound effect (SFX) */
	UPROPERTY(EditAnywhere, Category = "ShotEFX")
	class USoundBase* ShotSFX;

	/** The weapon`s Hit Effect, splash blood for organic targets */
	UPROPERTY(EditAnywhere, Category = "HitEFX")
	class UParticleSystem* HitBloodEFX;
	/** The weapon`s Hit Effect, bullet shatter for hard surface targets */
	UPROPERTY(EditAnywhere, Category = "HitEFX")
	class UParticleSystem* HitHardSurfaceEFX;

	/** The weapon`s Visual Hit Effect, decals for affected surface */
	UPROPERTY(EditAnywhere, Category = "HitEFX")
	class UMaterialInterface* HitDecalVFX;

	/** The weapon`s reload sound effect (SFX) */
	UPROPERTY(EditAnywhere, Category = "Reload")
	class USoundBase* ReloadSFX;

	/** The weapon`s out of ammo sound effect (SFX) */
	UPROPERTY(EditAnywhere, Category = "Reload")
	class USoundBase* OutOfAmmoSFX;

	/** ---------------  Weapon Atributes  --------------- */

	/**
	* The weapon ammunition amount.
	* The bullet rounds amount it can fire in a row
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	int32 WeaponAmmunitionAmount = 30;

	/** The weapon's magazine size */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	int32 WeaponMagazineSize = 3;

	/** The weapon magazine amount of bullets rounds. 
	(Ammo Amount * Magazine Size) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int32 WeaponMagazineAmount = WeaponAmmunitionAmount * WeaponMagazineSize;

	/** Manipulate the amount of damage the weapon can induce on Player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float DamageOnPlayer = 0.25f;

	/** Manipulate the amount of damage the weapon can induce on Enemies */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float DamageOnEnemy = 20.0f;

	/** Handle the weapon`s max range(and raycast range) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float WeaponMaxRange = 8000.0f;

	/** Handle the reload time interval */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float ReloadTimeInterval = 3.0f;

	/** Handles the time between shots */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float ShotInterval = 0.1f;

	/** Handles the Smooth Time to reset the Crosshair,
	The smaller the number, the faster it returns */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float SmoothCrosshairInterval = 0.01f;

	/** Handle the current weapon spread value, the smaller the value,
	more accurate it will be. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float WeaponSpreadCurrentValue = 0.0f;

	/**  The amount of value it will be increase after a consecultive shot */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float WeaponSpreadCoef = 1.5f;

protected:
	/** The amount of ammunition the weapon still has on it's chamber */
	int32 WeaponCurrentAmmunitionAmount = 0;

	/** Check if the weapon can shot*/
	bool bIsWeaponReloading = false;

	/** The Timer Handle for reloads */
	FTimerHandle ReloadTimerHandle;

};
