// 2023 Labverso, Brazil. Imersion Test.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	executionTime = 0.0f;
	deltaHeight = 0.0f;
	newLocation = FVector(0.0f, 0.0f, 0.0f);

}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	newLocation = this->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Nova Localização: %s\n"), *newLocation.ToString());

	deltaHeight = FMath::Sin(executionTime + DeltaTime) - FMath::Sin(executionTime);
	UE_LOG(LogTemp, Warning, TEXT("AlturaDelta: %f\n"), deltaHeight);

	newLocation.Z += deltaHeight * 20.0f;
	UE_LOG(LogTemp, Warning, TEXT("Nova Localização: %s\n"), *newLocation.ToString());

	executionTime += DeltaTime;
	UE_LOG(LogTemp, Warning, TEXT("Tempo de Execução: %f\n"), executionTime);

	this->SetActorLocation(newLocation);

}

