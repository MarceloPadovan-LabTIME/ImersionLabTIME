// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlamingSphere.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AFlamingSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlamingSphere();

private:
	//Declaração da variável ponteiro
	UPROPERTY(EditAnywhere, Category = "Componentes")
		UStaticMeshComponent* EsferaVisual;
	//class indica foward declaration?
	UPROPERTY(EditAnywhere, Category = "Componentes")
		class USphereComponent* EsferaDeColisao;
	//Ponteiro para um componente de sistema de particulas
	UPROPERTY(EditAnywhere, Category = "Componentes")
		UParticleSystemComponent* ParticulaDeFogo;

protected:
	UPROPERTY(EditAnywhere);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
