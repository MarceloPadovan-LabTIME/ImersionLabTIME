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

	bDeuHit = false;

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

	// Anexando a função OnComponentHit
	ColisorDoAtor->OnComponentHit.AddDynamic(this,
		&AACaixa::OcorreuHitNoComponente);

	// Para anexar uma função ao proprio Objeto use "this".
	this->OnActorHit.AddDynamic(this, &AACaixa::OcorreuHitNoAtor);
}

// Called when the game starts or when spawned
void AACaixa::BeginPlay()
{
	Super::BeginPlay();
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
		if (!bDeuHit)
		{
			SomDoHit->Activate(true);
			SomDoHit->Play(0);
			ParticulaHit->Activate(true);

			bDeuHit = true;
			OtherActor->Destroy();
		}	
	}
}

void AACaixa::OcorreuHitNoAtor(AActor* SelfActor, AActor* OtherActor, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning ,TEXT("Ator %s Bateu em: %s"), 
		*SelfActor->GetName(), *OtherActor->GetName());

	UE_LOG(LogTemp, Warning, TEXT("No local: %s"), 
		*Hit.ImpactPoint.ToString());
}

// Ao contrário de OnActorHit e OnComponentHit este evento será chamado quando
// ocorrer um hit sem a necessidade de anexarmos uma função delegate.
void AACaixa::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, 
	UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, 
	FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, 
		HitNormal, NormalImpulse, Hit);
	UE_LOG(LogTemp, Error, TEXT("Notificacao de HIT Realizada!"));

}


