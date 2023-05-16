// 2023 Labverso, Brazil. Imersion Test.


#include "ACaixa.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AACaixa::AACaixa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to
	// improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColisorDoAtor = CreateDefaultSubobject<UBoxComponent>(
		FName("Box Collider"));
	ColisorDoAtor->SetSimulatePhysics(true);
	ColisorDoAtor->SetNotifyRigidBodyCollision(true);
	ColisorDoAtor->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	RootComponent = ColisorDoAtor;

	

	MalhaDaCaixa = CreateDefaultSubobject<UStaticMeshComponent>(
		FName("Malha da Caixa"));
	MalhaDaCaixa->SetupAttachment(RootComponent);

	SomDoHit = CreateDefaultSubobject<UAudioComponent>(FName("Som Do Hit"));
	SomDoHit->bAutoActivate = false;
	SomDoHit->bStopWhenOwnerDestroyed = false;
	SomDoHit->SetupAttachment(RootComponent);

	ParticulaHit = CreateDefaultSubobject<UParticleSystemComponent>(
		FName("Particula"));
	ParticulaHit->bAutoActivate = false;
	ParticulaHit->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AACaixa::BeginPlay()
{
	Super::BeginPlay();
	
	ColisorDoAtor->OnComponentHit.AddDynamic(this, 
		&AACaixa::OcorreuHitNoComponente);
}

// Called every frame
void AACaixa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AACaixa::OcorreuHitNoComponente(UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	if ((OtherActor != nullptr)&& (OtherActor != this)&& (OtherComp != nullptr)
		&& OtherActor->ActorHasTag(FName("DestBox")))
	{
		SomDoHit->Activate(true);
		SomDoHit->Play(0);
		ParticulaHit->Activate(true);

		OtherActor->Destroy();
	}

}


