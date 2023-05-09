// 2023 Labverso, Brazil. Imersion Test.


#include "AtorQueRecebeInputs.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AAtorQueRecebeInputs::AAtorQueRecebeInputs()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to 
	// improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("Malha Estatica"));
	StaticMesh->SetSimulatePhysics(true);
	RootComponent = StaticMesh;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Minha Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->AddRelativeLocation(FVector(-330, 0, 130));

}

// Called when the game starts or when spawned
void AAtorQueRecebeInputs::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAtorQueRecebeInputs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAtorQueRecebeInputs::SetupPlayerInputComponent(UInputComponent*
	PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical Udemy", this, &AAtorQueRecebeInputs::MovimentoVertical);
	PlayerInputComponent->BindAxis("Horizontal Udemy", this, &AAtorQueRecebeInputs::RotacaoNoEixoZ);

}

void AAtorQueRecebeInputs::MovimentoVertical(float eixoVertical)
{
	FVector PosicaoAtual = GetActorLocation();
	FVector Frente = GetActorForwardVector();

	SetActorLocation(PosicaoAtual + (Frente * eixoVertical * Velocidade));

}

void AAtorQueRecebeInputs::RotacaoNoEixoZ(float eixoHorizontal)
{
	FRotator RotacaoAtual = GetActorRotation();
	FRotator eixoZ = FRotator::MakeFromEuler(FVector(0, 0, 1));
	SetActorRotation(RotacaoAtual + (eixoZ * eixoHorizontal * VelocidadeDeRotacao));
}

