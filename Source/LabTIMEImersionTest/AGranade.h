// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGranade.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AAGranade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAGranade();

	// Declara a função EndPlay que vai sobrescrever o
	// EndPlay de MeuGameModeTesteUdemy.
	// "virtual" indica que é uma função polimórfica(polimosfismo)
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle Temporizador, TimerDoSlowMotion;

	class UAudioComponent* SomDaExplosao;

	class UParticleSystemComponent* ExplosionEFX;

	UFUNCTION()
		void RadialImpulse(float range, float force);

	UFUNCTION()
		void ExplodirGranada();

	UFUNCTION()
		void SlowMotion(float DilatacaoDoTempo);

	UFUNCTION()
		void RestaurarTempo();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		float ExplosionRange = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		float ExplosionForce = 1000.f;

private:
	UPROPERTY(EditAnywhere, Category = "Visual")
	class UStaticMeshComponent* MalhaDoAtor;

	UPROPERTY(EditAnywhere, Category = "Visual")
	class USphereComponent* ColisorDoAtor;

	
};
