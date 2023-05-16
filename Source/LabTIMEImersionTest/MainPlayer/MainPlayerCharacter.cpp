// 2023 Labverso, Brazil. Imersion Test.


#include "MainPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystemComponent.h"

AMainPlayerCharacter::AMainPlayerCharacter()
{
	// Set size for collision capsule (yes, these values are hardcoded)
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create the first person camera component	
	FirstPersonCameraComponent = 
		CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	PrimaryActorTick.bCanEverTick = true;
}

void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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
		&APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("LookUp", this, 
		&APawn::AddControllerPitchInput);
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

