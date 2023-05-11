// 2023 Labverso, Brazil. Imersion Test.


#include "AInsertGranades.h"
#include "AGranade.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"

// Sets default values
AAInsertGranades::AAInsertGranades()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColisorDoAtor = CreateDefaultSubobject<USphereComponent>(FName("Colisor"));
	RootComponent = ColisorDoAtor;

}

// Called when the game starts or when spawned
void AAInsertGranades::BeginPlay()
{
	Super::BeginPlay();

	// Indica que iremos dar um Spawn de BpGranade.
	// BpGranade pode ser uma classe C++ ou Blueprint.
	// Sobrecarga de SpawnActor.
	GetWorld()->SpawnActor<AAGranade>(BpGranade, GetActorLocation(), GetActorRotation());
	
}

// Called every frame
void AAInsertGranades::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

