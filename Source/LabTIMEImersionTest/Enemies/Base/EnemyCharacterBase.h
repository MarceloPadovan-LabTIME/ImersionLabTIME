// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterBase.generated.h"

/** 
* This is the enemie's base character class. 
* This class deals with the base functionality of a enemy, e.g., it's movement.
* Extend this class for futher base functionalities.
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	/** Sets default values for this character's properties */
	AEnemyCharacterBase();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/**
	* A Reference of Weapon class, to spawn a BP copy in the character's hand
	* and use all its features, like shot action, realod action(WYP).
	*/
	class AWeaponBase* EnemyWeapon;

public: 
	/** Handles the changes of character`s Health values */
	UFUNCTION()
	void SetHealth(float Damage);

	/** Handles the return of current Health value */
	UFUNCTION()
	float GetHealth();

	/* This Function return the actual state about death/alive */
	UFUNCTION()
	bool bIsThisCharacterDead();

	/**/
	UFUNCTION()
		void Die();

	/**/
	UFUNCTION()
		void Respawn();

	/**/
	UFUNCTION()
		void PlaySpawnEFX();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:
	/* Let`s give a weapon to the enemy, like player */
	UPROPERTY(EditAnyWhere, Category = "Weapon")
	TSubclassOf<class AWeaponBase> BP_Weapon_AssaultRifle;

	/* Enemy main atribute, the health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Atributes")
	float Health;
	/** A flag to check if the enemy still alive or not,
	and trigger death animation */
	UPROPERTY(BlueprintReadOnly, Category = "Atibutes")
	bool bIsDead;

	/** Position to Respawn the Enemy*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	FVector RespawnLocation;

	/** A Visual Effect Play when the Enemy is Spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	class UParticleSystem* SpawnEFX = nullptr;

protected:
	/** The timer handle for the Enemy respawn */
	FTimerHandle RespawnTimerHandle;

	/** The Timer Handle for the New Enemies Spawn */
	FTimerHandle NewEnemySpawnTimerHandle;
};
