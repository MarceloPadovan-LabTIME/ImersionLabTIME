// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACaixa.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AACaixa : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACaixa();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Caixa")
	class UBoxComponent* ColisorDoAtor;

	UPROPERTY(EditAnywhere, Category = "Caixa")
	class UStaticMeshComponent* MalhaDaCaixa;

	UPROPERTY(EditAnywhere, Category = "Caixa")
	class UAudioComponent* SomDoHit;

	UPROPERTY(EditAnywhere, Category = "Caixa")
	class UParticleSystemComponent* ParticulaHit;

	UFUNCTION()
	void OcorreuHitNoComponente(UPrimitiveComponent* HitComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit);


};
