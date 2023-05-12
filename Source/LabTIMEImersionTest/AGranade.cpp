// 2023 Labverso, Brazil. Imersion Test.


#include "AGranade.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "EngineUtils.h"
#include "UObject/UObjectIterator.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/SkeletalMeshActor.h"
#include "UObject/UObjectBaseUtility.h"
#include "MainPlayer/MainPlayerCharacter.h"


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

	SomDaExplosao = CreateDefaultSubobject<UAudioComponent>(FName("Audio"));
	SomDaExplosao->bAutoActivate = false;
	SomDaExplosao->bAutoDestroy = true;
	SomDaExplosao->SetupAttachment(MalhaDoAtor);

	ExplosionEFX = CreateDefaultSubobject<UParticleSystemComponent>(
		FName("EFX"));
	ExplosionEFX->bAutoActivate = false;
	ExplosionEFX->bAutoDestroy = true;
	ExplosionEFX->SetupAttachment(MalhaDoAtor);


	
	ConstructorHelpers::FObjectFinder<UStaticMesh>Granade(
		TEXT("StaticMesh'/Game/Art/Meshes/Granade/granada.granada'"));

	ConstructorHelpers::FObjectFinder<USoundCue>SomGranade(
		TEXT("SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));

	ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleExplosionEFX(TEXT(
		"ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	if (Granade.Succeeded() && SomGranade.Succeeded() &&
		ParticleExplosionEFX.Succeeded())
	{
		MalhaDoAtor->SetStaticMesh(Granade.Object);
		SomDaExplosao->SetSound(SomGranade.Object);
		ExplosionEFX->SetTemplate(ParticleExplosionEFX.Object);
	}
}

void AAGranade::EndPlay(const EEndPlayReason::Type EndPlayReason)
{  
	Super::EndPlay(EndPlayReason);

	// Será colocado na tela durante 5 segundos(5.f) em cor vermelha
	// o texto indicado.
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		//"Granade Destroyed!");

	// Aqui estamos exluindo o manipulador(handle) de nome Temporatizador
	// A partir daqui ele será invalidado.
	GetWorldTimerManager().ClearTimer(Temporizador);
}

// Called when the game starts or when spawned
void AAGranade::BeginPlay()
{
	Super::BeginPlay();

	SlowMotion(0.1f);

	MalhaDoAtor->SetSimulatePhysics(true);
	MalhaDoAtor->SetEnableGravity(true);

	GetWorldTimerManager().SetTimer(Temporizador, this, 
		&AAGranade::ExplodirGranada, 5.0f, false);
	
}

// Called every frame
void AAGranade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAGranade::RadialImpulse(float range, float force)
{
	for (TActorIterator<AStaticMeshActor>
		ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nome: %s"), *ActorItr->GetName(),
			*ActorItr);

		UStaticMeshComponent* RootComponentDoStaticMesh;

		RootComponentDoStaticMesh = Cast<UStaticMeshComponent>(
			ActorItr->GetRootComponent());

		if (RootComponentDoStaticMesh)
		{
			// Adicionar na condição:
			// && (ActorItr->GetName() == FString("CadeiraEsquerda"))
			// para verificar o nome do Ator/Objeto
			// Adicionar na condição:
			// && (ActorItr->ActorHasTag(FName("Cadeira")))
			if (RootComponentDoStaticMesh->Mobility == 
				EComponentMobility::Movable && (ActorItr->ActorHasTag(FName("Cadeira"))))
			{
				RootComponentDoStaticMesh->SetSimulatePhysics(true);
				RootComponentDoStaticMesh->AddRadialImpulse(GetActorLocation(),
					range, force, ERadialImpulseFalloff::RIF_Linear, true);
			}
		}
	}

	for (TObjectIterator<USkeletalMeshComponent> It; It; ++It)
	{
		if (It->GetWorld() == GetWorld())
		{
			if (It->ComponentHasTag(FName("Playercpp")))
			{
				UE_LOG(LogTemp, Warning, TEXT("Name: %s Adress: %X \n"), 
					*It->GetName(), *It);

				ACharacter* OutroInimigo = Cast<ACharacter>(It->GetOwner());

				UParticleSystemComponent* Particula = Cast<
					UParticleSystemComponent>(OutroInimigo->GetComponentByClass(
						UParticleSystemComponent::StaticClass()));

				Particula->Activate(true);

				It->SetSimulatePhysics(true);

				It->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				It->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

				It->AddRadialImpulse(GetActorLocation(), range, force,
					ERadialImpulseFalloff::RIF_Linear, true);
			}
		}
	}
}

void AAGranade::ExplodirGranada()
{
	SetLifeSpan(5.5f);
	SomDaExplosao->Play();
	SlowMotion(0.05);
	ExplosionEFX->ActivateSystem();
	MalhaDoAtor->SetVisibility(false);
	RadialImpulse(ExplosionRange, ExplosionForce);
}

void AAGranade::SlowMotion(float DilatacaoDoTempo)
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), DilatacaoDoTempo);
	GetWorldTimerManager().SetTimer(TimerDoSlowMotion, this, 
		&AAGranade::RestaurarTempo, (3.f* DilatacaoDoTempo), false);
}

void AAGranade::RestaurarTempo()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	GetWorldTimerManager().ClearTimer(TimerDoSlowMotion);
}

