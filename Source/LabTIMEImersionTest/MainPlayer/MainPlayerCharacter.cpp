// 2023 Labverso, Brazil. Imersion Test.


#include "MainPlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/SpringArmComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "LabTIMEImersionTest/Weapons/Base/AutomaticWeapon.h"
#include "Engine/EngineTypes.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "WorldCollision.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/LatentActionManager.h"



AMainPlayerCharacter::AMainPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule (yes, these values are hardcoded)
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create the Spring Arm Camera, to use its functionalities, boom effects,
	// smooth movements, and even more.
	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(
		FName("SpringArm"));
	SpringArmCamera->TargetArmLength = 200.f;
	SpringArmCamera->bUsePawnControlRotation = true;
	SpringArmCamera->AddRelativeLocation(FVector(0.f, 40.f, 50.f));
	SpringArmCamera->SetupAttachment(RootComponent);

	// Create the first person camera component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(
		TEXT("FirstPersonCamera"));
	//FirstPersonCameraComponent->SetupAttachment(GetMesh());
	FirstPersonCameraComponent->AttachToComponent(Cast<USceneComponent>(GetMesh()),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("Head_Socket"));
	

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->AirControl = 3.0f;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->CrouchedHalfHeight = 70.f;
}

void AMainPlayerCharacter::SetHealth(float Damage)
{
	// Check if the Player still have Health.
	if (Health > 0.0f)
	{
		Health -= Damage;
	}

	// Check if the Player took enough damage to be dead.
	else if (Health <= 0.0f)
	{
		//Health = 0.0f;
		Die();
	}
	
}

float AMainPlayerCharacter::GetHealth()
{
	return Health;
}

bool AMainPlayerCharacter::bIsThisCharacterDead()
{
	return bIsDead;
}

void AMainPlayerCharacter::Die()
{
	// A flag that indicates the player is dead.
	bIsDead = true;

	// Locate the player controller across the scene, and returns it. 
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	// Ensures that the controller was found,
	// preventing Unreal from crashing.
	check(PlayerController);

	// Uses the found PlayerController object to disable player inputs.
	// thus preventing the character from moving when dying.
	PlayerController->GetPawn()->DisableInput(PlayerController);
}

void AMainPlayerCharacter::Respawn()
{
	//Set the actor location to the start location.
	// Give the characater back to live.
	// Give back the input controllers.
}

void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Ensures that the player character will be possess when the game starts.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a parameter which will ensure that where will be no
	// collision conflicts
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = 
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn this character's weapon.
	PlayerPrimaryWeapon = GetWorld()->SpawnActor<
		AWeaponBase>(BP_Weapon, FTransform(), Params);

	// Attach the weapon to the character hand socket, previously created.
	PlayerPrimaryWeapon->AttachToComponent(Cast<USceneComponent>(GetMesh()),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("Socket_Weapon"));

}

void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainPlayerCharacter::SetupPlayerInputComponent
	(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the forward and right movement of the character
	PlayerInputComponent->BindAxis("MoveForward", this, 
		&AMainPlayerCharacter::MoveCharacterForward);
	PlayerInputComponent->BindAxis("MoveRight", this, 
		&AMainPlayerCharacter::MoveCharacterRight);

	// Bind the controller Yaw and Pitch movement 
	PlayerInputComponent->BindAxis("Turn", this, 
		&AMainPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, 
		&AMainPlayerCharacter::AddControllerPitchInput);

	// Bind the crouch and uncrouch action
	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::MyCrouch);
	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Released, this,
		&AMainPlayerCharacter::StandUp);

	// Bind the jump action
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, 
		&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, 
		&ACharacter::StopJumping);
	
	// Bind the Fire with a weapon action
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this,
		&AMainPlayerCharacter::StopFiring);

	// Bind the Weapon reload action
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::WeaponReload);

}

void AMainPlayerCharacter::MoveCharacterForward(float AxisValue)
{
	// Add movement on forward direction given the axis value
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void AMainPlayerCharacter::MoveCharacterRight(float AxisValue)
{
	// Add movement on right direction given the axis value
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void AMainPlayerCharacter::MyCrouch()
{
	Crouch();
}

void AMainPlayerCharacter::StandUp()
{
	UnCrouch();
}

void AMainPlayerCharacter::MyJump()
{
	bIsJumping = true;

	float X = GetCapsuleComponent()->GetRelativeLocation().X;
	float Y = GetCapsuleComponent()->GetRelativeLocation().Y + 40;
	float Z = GetCapsuleComponent()->GetRelativeLocation().Z + 100;

	FRotator CapsuleRot = GetCapsuleComponent()->GetRelativeRotation();

	FLatentActionInfo LatentInfo;

	LatentInfo.CallbackTarget = this;

	LatentInfo.UUID = GetUniqueID();

	LatentInfo.ExecutionFunction = "Jump";

	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::MoveComponentTo(GetCapsuleComponent(),
		FVector(X, Y, Z), CapsuleRot, false, false, 0.5f, false,
		EMoveComponentAction::Move, LatentInfo);
}

void AMainPlayerCharacter::JumpNotAllowed()
{
	bIsJumping = false;
}

void AMainPlayerCharacter::Fire()
{
	bIsShooting = true;
	PlayerPrimaryWeapon->FireWeapon();
}

void AMainPlayerCharacter::StopFiring()
{
	bIsShooting = false;
	PlayerPrimaryWeapon->StopFiringWeapon();
}

void AMainPlayerCharacter::WeaponReload()
{
	PlayerPrimaryWeapon->Reload();
}

