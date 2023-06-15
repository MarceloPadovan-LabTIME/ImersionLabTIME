// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayerCharacter.generated.h"

/** 
* This class deals with the main character of the game.
* A important functionality is the character movement handling.
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Handles the changes of character`s Health values */
	UFUNCTION()
	void SetHealth(float Damage);

	/** Handles the return of current Health value */
	UFUNCTION()
	float GetHealth();

	/** Check the character`s current status regarding life and death */
	UFUNCTION()
	bool bIsThisCharacterDead();

	/** 
	* Called when the character dies, launch the bIsDead flag,
	* play death animation, and take out all of the inputs received by player.
	*/
	UFUNCTION()
	void Die();

	/** 
	* Handles the character's respawn. After dying, the character will be
	* repawned at random location to continue acting until the game's mode end.
	* Or call the GameOver state, and reload the scene.
	*/
	UFUNCTION()
	void Respawn();

	/** Handles the player's double jump action. */
	UFUNCTION()
	void DoubleJump();

public:
	/** Sets default values for this character's properties */
	AMainPlayerCharacter();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(
	class UInputComponent* PlayerInputComponent) override;

	/** 
	* Handles the forward movement of the character. 
	* This method should be binded on a axis input.
	* 
	* @param AxisValue The axis value of the input 
	*/
	void MoveCharacterForward(float AxisValue);

	/**
	* Handles the right movement of the character.
	* This method should be binded on a axis input.
	*
	* @param AxisValue The axis value of the input
	*/
	void MoveCharacterRight(float AxisValue);

	/** Handles the crouch action of the character */
	void MyCrouch();

	/** Handles the stand up action of the character */
	void StandUp();

	/** Handles the jump action of the character. */
	void MyJump();

	/** 
	* Handles the jump state not allow to jump of the character.
	* Ensures that player will not jump at inappropriate times.
    */
	void JumpNotAllowed();

	/** Handles the sprint action of player characater */
	void Sprint();

	/** Stop the Sprint action */
	void StopSprint();

	/** Handles the Sneak action, more precise movement, but slowly*/
	void Sneak();

	/** Handles the stop sneaking action of the player characater */
	void StopSneaking();

	/** Handles the fire action of the player character */
	void Fire();

	/** Handle the stop firing action of the player character */
	void StopFiring();

	/** Handles the aiming down sight with a weapon action */
	void Aiming();

	/** Handles the Stop aiming down sight with a weapon action */
	void StopAiming();

	/** Handles the action of reloading a weapon*/
	void WeaponReload();

	/** Handles the action of selecting the first weapon of Array */
	void SelectFirstWeapon();
	/** Handles the action of selecting the second weapon of Array */
	void SelectSecondWeapon();
	/** Handles the action of selecting the third weapon of Array */
	void SelectThirdWeapon();

	/** Handles the action of switching for the next weapon */
	void SwitchNextWeapon();
	/** Handles the action of switching for the previous weapon */
	void SwitchPreviousWeapon();

public:
	/** 
	* A Array of weapons, spawned in BeginPlay, this array store all weapons
	* the player can have at same time. 
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TArray<class AWeaponBase*> WeaponsArray;

	/**
    * A Reference of Weapon class, to spawn a BP copy in the character's hand
	* and use all its features, like shot action, realod action(WYP).
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	class AWeaponBase* PlayerPrimaryWeapon;

	/** Flag for checking Jumping States. */
	UPROPERTY(BlueprintReadWrite, Category = "Info")
	bool bIsJumping;

	/** Flag for checking the Shooting States. */
	UPROPERTY(BlueprintReadWrite, Category = "Info")
	bool bIsShooting;

	/** Flag: indicates the player is reloading the gun */
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	bool bIsReloadingWeapon;

	/** Flag: indicates the player is aiming with the gun, used in animation */
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	bool bIsAiming;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:
	//UFUNCTIONS

protected:
	/** Spawn all player weapons at BeginPlay */
	void SpawnWeapons();
	
	/** Handles the landed state of player(player hitting the ground) */
	virtual void Landed(const FHitResult& Hit) override;

protected:
	/** Create a reference for player list of weapons. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TArray<TSubclassOf<AWeaponBase>> BP_Weapon;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, 
		Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent = nullptr;

	/** First person spring arm camera, camera boom */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
		Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmCamera = nullptr;

	/** Main atribute of the player character, health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health = 100.0f;

	/** The speed multiply for Sneak velocity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float SneakSpeedCoef = 0.6f;

	/** The speed multiply for character movement velocity, run action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float SprintSpeedCoef = 2.0f;

	/** Flag: indicates the player is Dead or not */
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	bool bIsDead;

	/** A position to respawn when killed */
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	FVector RespawnLocation;

	/** Count the jump number, with this we can enable the double jump. */
	UPROPERTY()
	int DoubleJumpCounter;

	/** New height of the jump, used to launch the character into the air.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float JumpHeight = 600.f;

	/** Ptr to reference the main GameMode script. */
	//UPROPERTY()
	//class ALabTIMEImersionTestGameModeBase* MainGameMode = nullptr;

protected:
	//Non-UPROPERTIES

private:
	/** 
	* This function is called when the player dies, after a few seconds,
	* the level is reset.
	*/
	void RestartLevelWhenDie();

private:
	/** The restart game timer handle, used when player dies
	or terminate loops. */
	FTimerHandle RestartGameTimerHandle;

};
