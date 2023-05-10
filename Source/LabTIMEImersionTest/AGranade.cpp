// 2023 Labverso, Brazil. Imersion Test.


#include "AGranade.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AAGranade::AAGranade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to
	// improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColisorDoAtor = CreateDefaultSubobject<USphereComponent>(FName("Colisor"));
	ColisorDoAtor->SetSphereRadius(12.0f);
	ColisorDoAtor->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = ColisorDoAtor;

	MalhaDoAtor = CreateDefaultSubobject<UStaticMeshComponent>(FName("Malha"));
	MalhaDoAtor->SetRelativeLocation(FVector(3.2f, 0.f, 0.f));
	MalhaDoAtor->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	MalhaDoAtor->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh>Granade(
		TEXT("StaticMesh'/Game/Art/Meshes/Granade/granada.granada'"));

	if (Granade.Succeeded())
	{
		MalhaDoAtor->SetStaticMesh(Granade.Object);
	}
}

// Called when the game starts or when spawned
void AAGranade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAGranade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

