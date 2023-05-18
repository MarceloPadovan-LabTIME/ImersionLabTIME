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

	// Handles the jump action of the character.
	void MyJump();

	// Handles the jump state not allow to jump of the character.
	// Ensures that player will not jump at inappropriate times.
	void JumpNotAllowed();

public:
	// Flag for checking Jumping States.
	UPROPERTY(BlueprintReadOnly, Category = "Jump")
		bool bIsJumping;
	
	//
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class AAutomaticWeapon> BP_Weapon_AssaultRifle;


protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

protected:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, 
		Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent = nullptr;

};
