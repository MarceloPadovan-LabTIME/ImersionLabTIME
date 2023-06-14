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
#include "LabTIMEImersionTest/Weapons/Base/WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "WorldCollision.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/LatentActionManager.h"
#include "Containers/Array.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LabTIMEImersionTest/LabTIMEImersionTestGameModeBase.h"

// Constructor
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

	//Create the first person camera component
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(
		TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	/*FirstPersonCameraComponent->AttachToComponent(Cast<USceneComponent>(GetMesh()),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("Head_Socket"));*/

	// Jump & Crouch Config.
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->AirControl = 3.0f;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->CrouchedHalfHeight = 70.f;
}

void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Ensures that the player character will be possess when the game starts.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SpawnWeapons();
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

	// Bind the Sneak type movement speed of the characater
	PlayerInputComponent->BindAction("Sneak", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::Sneak);
	PlayerInputComponent->BindAction("Sneak", EInputEvent::IE_Released, this,
		&AMainPlayerCharacter::StopSneaking);

	// Bind the Sprint type movement of the characater
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this,
		&AMainPlayerCharacter::StopSprint);

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
		&AMainPlayerCharacter::DoubleJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this,
		&ACharacter::StopJumping);

	// Bind the Fire with a weapon action
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this,
		&AMainPlayerCharacter::StopFiring);

	// Bind the Aiming with a weapon action
	PlayerInputComponent->BindAction("Aiming", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::Aiming);
	PlayerInputComponent->BindAction("Aiming", EInputEvent::IE_Released, this,
		&AMainPlayerCharacter::StopAiming);

	// Bind the Weapon reload action
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::WeaponReload);

	// Bind the Swap Weapon action
	// Next Weapon
	PlayerInputComponent->BindAction("SwitchNextWeapon",
		EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::SwitchNextWeapon);
	// Previous Weapon
	PlayerInputComponent->BindAction("SwitchPreviousWeapon",
		EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::SwitchPreviousWeapon);

	// Bind the fixed weapon selection and hot keys.
	PlayerInputComponent->BindAction("Weapon_1", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::SelectFirstWeapon);
	PlayerInputComponent->BindAction("Weapon_2", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::SelectSecondWeapon);
	PlayerInputComponent->BindAction("Weapon_3", EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::SelectThirdWeapon);
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

	GetWorldTimerManager().SetTimer(RestartGameTimerHandle, this,
		&AMainPlayerCharacter::RestartLevelWhenDie, 8.0f, false);
}

void AMainPlayerCharacter::RestartLevelWhenDie()
{
	//GetGameMode and uses your RestartLevel() function.

	ALabTIMEImersionTestGameModeBase* MainGameMode = Cast<ALabTIMEImersionTestGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!MainGameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("Main GameMode not found."));
	}

	MainGameMode->ResetLevel();
}

void AMainPlayerCharacter::Respawn()
{
	//Set the actor location to the start location.
	// Give the characater back to live.
	// Give back the input controllers.
}

void AMainPlayerCharacter::DoubleJump()
{
	if (DoubleJumpCounter <= 1)
	{
		ACharacter::LaunchCharacter(FVector(0, 0, JumpHeight), false, true);

		DoubleJumpCounter++;
	}
}

void AMainPlayerCharacter::Landed(const FHitResult& Hit)
{
	DoubleJumpCounter = 0;
}

void AMainPlayerCharacter::SpawnWeapons()
{
	// Create a parameter which will ensure that where will be no
	// collision conflicts
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	int32 Index = 0;
	for (const TSubclassOf<AWeaponBase>& Weapons : BP_Weapon)
	{
		// Spawn this character's weapon.
		AWeaponBase *WeaponToSpawn = GetWorld()->SpawnActor<
			AWeaponBase>(Weapons, FTransform(), Params);
		if (!WeaponToSpawn)
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to spawn weapon in world."));

			return;
		}
		// Add the spawned weapon to the Arraylist.
		WeaponsArray.Add(WeaponToSpawn);

		// Attach the weapon to the character hand socket, previously created.
		WeaponsArray[Index]->AttachToComponent(Cast<USceneComponent>
			(GetMesh()), FAttachmentTransformRules::SnapToTargetIncludingScale,
			FName("Socket_Weapon"));

		// Hide(disable) the Spawned weapon.
		WeaponsArray[Index]->SetActorHiddenInGame(true);

		Index++;
	}

	PlayerPrimaryWeapon = WeaponsArray[0];
	PlayerPrimaryWeapon->SetActorHiddenInGame(false);
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

void AMainPlayerCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedCoef;
}

void AMainPlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedCoef;
}

void AMainPlayerCharacter::Sneak()
{
	GetCharacterMovement()->MaxWalkSpeed *= SneakSpeedCoef;
}

void AMainPlayerCharacter::StopSneaking()
{
	GetCharacterMovement()->MaxWalkSpeed /= SneakSpeedCoef;
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

void AMainPlayerCharacter::Aiming()
{
	bIsAiming = true;

	FirstPersonCameraComponent->Deactivate();
	PlayerPrimaryWeapon->AimingCameraComponent->Activate();

	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(
		PlayerPrimaryWeapon, 0.25f);
}

void AMainPlayerCharacter::StopAiming()
{
	bIsAiming = false;

	PlayerPrimaryWeapon->AimingCameraComponent->Deactivate();
	FirstPersonCameraComponent->Activate();

	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(
		this, 0.25f);
}

void AMainPlayerCharacter::WeaponReload()
{
	PlayerPrimaryWeapon->Reload();
}

void AMainPlayerCharacter::SelectFirstWeapon()
{
	PlayerPrimaryWeapon = WeaponsArray[0];
	WeaponsArray[0]->SetActorHiddenInGame(false);

	WeaponsArray[1]->SetActorHiddenInGame(true);
	WeaponsArray[2]->SetActorHiddenInGame(true);
}

void AMainPlayerCharacter::SelectSecondWeapon()
{
	PlayerPrimaryWeapon = WeaponsArray[1];
	PlayerPrimaryWeapon->SetActorHiddenInGame(false);

	WeaponsArray[0]->SetActorHiddenInGame(true);
	WeaponsArray[2]->SetActorHiddenInGame(true);
}

void AMainPlayerCharacter::SelectThirdWeapon()
{
	PlayerPrimaryWeapon = WeaponsArray[2];
	PlayerPrimaryWeapon->SetActorHiddenInGame(false);

	WeaponsArray[0]->SetActorHiddenInGame(true);
	WeaponsArray[1]->SetActorHiddenInGame(true);
}

void AMainPlayerCharacter::SwitchNextWeapon()
{
	for (int i = 0; i < WeaponsArray.Num(); i++)
	{
		if (PlayerPrimaryWeapon == WeaponsArray[i] 
			&& i < WeaponsArray.Num() - 1)
		{
			WeaponsArray[i]->SetActorHiddenInGame(true);
			PlayerPrimaryWeapon = WeaponsArray[i+1];
			WeaponsArray[i+1]->SetActorHiddenInGame(false);

			return;
		}
		else if (PlayerPrimaryWeapon == WeaponsArray[i] 
			&& i==WeaponsArray.Num()-1) 
		{
			WeaponsArray[i]->SetActorHiddenInGame(true);
			PlayerPrimaryWeapon = WeaponsArray[0];
			WeaponsArray[0]->SetActorHiddenInGame(false);

			return;
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("WeaponName: %s"), 
		*FString(PlayerPrimaryWeapon->GetWeaponName()));
}

void AMainPlayerCharacter::SwitchPreviousWeapon()
{
	for (int i = 0; i < WeaponsArray.Num(); i++)
	{
		if (PlayerPrimaryWeapon == WeaponsArray[i] && i > 0)
		{
			WeaponsArray[i]->SetActorHiddenInGame(true);
			PlayerPrimaryWeapon = WeaponsArray[i - 1];
			WeaponsArray[i-1]->SetActorHiddenInGame(false);
			return;
		}
		else if (PlayerPrimaryWeapon == WeaponsArray[i] && i == 0 )
		{
			WeaponsArray[i]->SetActorHiddenInGame(true);
			PlayerPrimaryWeapon = WeaponsArray[WeaponsArray.Num() - 1];
			WeaponsArray[WeaponsArray.Num() - 1]->SetActorHiddenInGame(false);
			return;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("WeaponName: %s"), 
		*FString(PlayerPrimaryWeapon->GetWeaponName()));
}