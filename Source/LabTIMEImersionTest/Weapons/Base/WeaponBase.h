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
	/** Spawn a Muzzle Effect when a shot is taken */
	void SpawnMuzzleEFX();

	/** Every time a shot is made, this function will play the shot sound */
	void PlayGunshotSoundEFX(FVector PlaySoundLocation);

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

	/** Weapon Atributes */
	/** Manipulate the amount of damage the weapon can induce on Player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Atributes")
	float DamageOnPlayer = 0.25f;
	/** Manipulate the amount of damage the weapon can induce on Enemies */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Atributes")
	float DamageOnEnemy = 20.0f;

	/** Handle the weapon`s max range(and raycast range) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Atributes")
	float WeaponMaxRange = 8000.0f;


protected:
	/** The amount of ammunition the weapon still has on it's chamber */
	int32 WeaponCurrentAmmunitionAmount = 0;
};
