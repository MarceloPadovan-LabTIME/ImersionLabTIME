// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "APickUpAmmo.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AAPickUpAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPickUpAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Box Collider Properties
	UPROPERTY(EditAnywhere, Category = "PickUpAmmo")
		class UBoxComponent* ColisorDoAtor;

	// Visual Properties
	UPROPERTY(EditAnywhere, Category = "PickUpAmmo")
		class UStaticMeshComponent* MalhaDoAtor;

	UPROPERTY(EditAnywhere, Category = "PickUpAmmo")
		class UParticleSystemComponent* PickUpVFX;

	// In Game FloatingText Properties
	UPROPERTY(EditAnywhere, Category = "PickUpAmmo")
		class UTextRenderComponent* FloatingText;
	
	// Audio Properties
	UPROPERTY(EditAnywhere, Category = "PickUpAmmo")
		class UAudioComponent* PickUpSFX;

	// Pick UP EFX Properties
	UPROPERTY(EditAnywhere, Category = "PickUpAmmo")
		class UParticleSystemComponent* AfterPickUpVFX;

	UFUNCTION()
		void PickUpItemAmmo(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
