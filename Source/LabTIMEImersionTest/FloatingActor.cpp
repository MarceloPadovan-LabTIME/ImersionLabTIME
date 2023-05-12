// 2023 Labverso, Brazil. Imersion Test.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to 
	// improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	executionTime = 0.0f;
	deltaHeight = 0.0f;
	newLocation = FVector(0.0f, 0.0f, 0.0f);

}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	if (bIsTarget)
	{
		// Cria variavel que recebe um numero aleatório.
		const float RandomRotation = FMath::RandRange(MinRotation, MaxRotation);
		const float RandomPosition = FMath::RandRange(MinPosition, MaxPosition);
		const float RandomScale = FMath::RandRange(MinScale, MaxScale);

		// Cria uma variavel de vetor para armazenar os valores aleatórios.
		const FRotator RngRot = FRotator(RandomRotation);
		const FVector RngPos = FVector(RandomPosition);
		const FVector RngScl = FVector(RandomScale);

		// Cria uma variavel do tipo FTransform que recebe as Structs de
		// Rotação, Posição e Escala de Objetos.
		FTransform newTransform = FTransform(RngRot, RngPos, RngScl);
		
		//Estabelece uma nova Transform ao ator.
		AddActorLocalTransform(newTransform);
	}
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotation
	AddActorLocalRotation(FRotator(0, 50, 0) * DeltaTime * RotationSpeed);

	// Floating
	newLocation = this->GetActorLocation();
	deltaHeight = FMath::Sin(executionTime + DeltaTime) 
		- FMath::Sin(executionTime);
	newLocation.Z += deltaHeight * 20.0f;
	executionTime += DeltaTime;
	this->SetActorLocation(newLocation);

}

