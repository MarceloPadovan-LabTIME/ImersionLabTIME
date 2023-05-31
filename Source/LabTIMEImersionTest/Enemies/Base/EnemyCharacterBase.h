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

	/** Handles the consequences of dying, animation, stop acting, and more */
	UFUNCTION()
		void Die();

	/** Handles the Enemy Respawn, The same actor return to life */
	UFUNCTION()
		void Respawn();

	/** Handles the Spawn VisualEffect When the Enemy is Spawned in the scene*/
	UFUNCTION()
	void PlaySpawnEFX();

	/** Add a Score value to the current player's score */
	UFUNCTION()
	void AddPlayerScore();

public:

	/** 
	* A flag to check if the enemy still alive or not,
	* and trigger death animation. 
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	bool bIsDead;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:
	/** Gives a Weapon to the Enemy. Otherwise is not a fair play. */
	UFUNCTION()
		void GetAWeapon();

protected:
	/* Let`s give a weapon to the enemy, like player */
	UPROPERTY(EditAnyWhere, Category = "Weapon")
	TSubclassOf<class AWeaponBase> BP_Weapon_AssaultRifle;

	/* Enemy main atribute, the health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float Health;

	/* 
	* Enemy's attribute, the armor. This atribute handles the amout of damage
	* the enemy characater can reduce before being inflicted on Health value
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float Armor = 50.f;

	/* 
	* Armor's complementation, this value is a percentage that represents
	* how much damage will be reduced.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float ArmorEffectiveness = 75.f;



	/** The amount of scores point the player will receive after a kill */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 EnemyRewardScore = 1;

	/** Position to Respawn the Enemy*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	FVector RespawnLocation;

	/** A Visual Effect Play when the Enemy is Spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	class UParticleSystem* SpawnEFX = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	class ALabTIMEImersionTestGameModeBase* MainGameMode = nullptr;

protected:
	/** The timer handle for the Enemy respawn */
	FTimerHandle RespawnTimerHandle;

	/** The Timer Handle for the New Enemies Spawn */
	FTimerHandle NewEnemySpawnTimerHandle;
};
