// 2023 Labverso, Brazil. Imersion Test.


#include "APickUpAmmo.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AAPickUpAmmo::AAPickUpAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to
	// improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColisorDoAtor = CreateDefaultSubobject<UBoxComponent>(
		FName("Box Collider"));
	ColisorDoAtor->InitBoxExtent(FVector(10.f,10.f,10.f));
	ColisorDoAtor->SetCollisionProfileName("Trigger");
	RootComponent = ColisorDoAtor;

	MalhaDoAtor = CreateDefaultSubobject<UStaticMeshComponent>(
		FName("Malha Visual"));
	MalhaDoAtor->SetRelativeLocation(FVector(0.f, 0.f, 16.f));
	MalhaDoAtor->SetupAttachment(RootComponent);

	PickUpVFX = CreateDefaultSubobject<UParticleSystemComponent>(FName("VFX"));
	PickUpVFX->SetupAttachment(MalhaDoAtor);
	PickUpVFX->bAutoActivate = true;

	FloatingText = CreateDefaultSubobject<UTextRenderComponent>(
		FName("Texto Flutuante"));
	FloatingText->SetupAttachment(MalhaDoAtor);
	FloatingText->SetHorizontalAlignment(EHTA_Center);
	FloatingText->SetXScale(1.f);
	FloatingText->SetYScale(1.f);
	FloatingText->SetTextRenderColor(FColor::Yellow);
	FloatingText->SetVisibility(true);

	PickUpSFX = CreateDefaultSubobject<UAudioComponent>(
		FName("PickUp Audio SFX"));
	PickUpSFX->bAutoActivate = false;
	PickUpSFX->SetupAttachment(RootComponent);

	AfterPickUpVFX = CreateDefaultSubobject<UParticleSystemComponent>(
		FName("PickUp EFX"));
	AfterPickUpVFX->SetupAttachment(RootComponent);
	AfterPickUpVFX->bAutoActivate = false;

	ColisorDoAtor->OnComponentBeginOverlap.AddDynamic(
		this, &AAPickUpAmmo::PickUpItemAmmo);


}

// Called when the game starts or when spawned
void AAPickUpAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPickUpAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(16, 32, 16), 
		FColor::Red, true, -1, 0, 0.15f);

}

void AAPickUpAmmo::PickUpItemAmmo(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(
		TEXT("Entrou no Trigger Loc: %s"), *GetActorLocation().ToString()));

	if ((OtherActor != nullptr) &&
		(OtherActor != this) &&
		(OtherComp != nullptr))
	{
		// Debugging
		// OverlappedComponent é o componente deste ator(PickUpAmmo)
		UE_LOG(LogTemp, Error, TEXT("OverlappedComponent = %s "),
			*OverlappedComp->GetName());

		// OtherActor é o ator que sobrepõe este ator
		UE_LOG(LogTemp, Warning, TEXT("OtherActor = %s "), 
			*OtherActor->GetName());

		// OtherComp é o componente de OtherActor que realizou a sobreposição
		UE_LOG(LogTemp, Error, TEXT("OtherComp = %s "), *OtherComp->GetName());

		// OtherBodyIndex: O índice do componente que está sendo sobreposto.
		UE_LOG(LogTemp, Warning, TEXT("OtherBodyIndex = %d "), OtherBodyIndex);




		PickUpSFX->Activate(true);
		// bStopWhenOwnerDestroyed: Indica que o som não irá parar caso o 
		// proprietário deste componente de som seja destruído.
		PickUpSFX->bStopWhenOwnerDestroyed = false;
		PickUpSFX->Play(0.0f);

		AfterPickUpVFX->ActivateSystem();

		Destroy();
	}
}

