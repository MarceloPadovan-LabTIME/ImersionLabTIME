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
	
	UPROPERTY(EditAnywhere, Category = "Variaveis")
	bool VariavelEditAnwhere;

	UPROPERTY(VisibleAnywhere, Category = "Variaveis")
	float VariavelVisibleAnywhere;

	UPROPERTY(EditDefaultsOnly, Category = "Variaveis")
	float VariavelEditDefaltsOnly;

	UPROPERTY(VisibleDefaultsOnly, Category = "Variaveis")
	float VariavelVisibleDefaultsOnly;

	UPROPERTY(BlueprintReadWrite, Category = "Variaveis")
	FVector VariavelBlueprintReadWrite = FVector(0.f, 0.f, -180.f);

	UPROPERTY(BlueprintReadOnly, Category = "Variaveis")
	FString VariavelBlueprintReadOnly = "Texto Blueprint";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variaveis")
	FString VariavelEditAnywhereBlueprintReadWrite = "Texto Editavel";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variaveis")
	FString VariavelEditAnywhereBlueprintReadOnly = "Texto apenas visivel";

	UFUNCTION()
		void InicioSobreposicao(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void FimSobreposicao(AActor* OverlappedActor, AActor* OtherActor);

	//Foward Declaration
	class UTextRenderComponent* TextoDeExibicao;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
