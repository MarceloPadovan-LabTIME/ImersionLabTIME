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
	//Declara��o da vari�vel ponteiro
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


	// Macro UFUNCTION: define funcoes e pode receber parametros.
	UFUNCTION(BlueprintNativeEvent, Category = "Sobreposicoes")
	void InicioSobreposicao(AActor* OverlappedActor, AActor* OtherActor);

	void InicioSobreposicao_Implementation(AActor* OverlappedActor,
		AActor* OtherActor);

	// BlueprintNativeEvent:
	// Cria uma fun�ao que ser� implementada na Blueprint,
	// Entetando, existe uma declara��o implementada no c�digo C++.
	// Caso essa fun�ao nao seja customizada dentro do editor da Blueprint,
	// A fun�ao declarada no codigo ser� executada como padrao.
	UFUNCTION(BlueprintNativeEvent, Category = "Sobreposicoes")
	void FimSobreposicao(AActor* OverlappedActor, AActor* OtherActor);

	// Esta fun��o ser� chamada caso a blueprint n�o a sobreescreva.
	void FimSobreposicao_Implementation(AActor* OverlappedActor,
		AActor* OtherActor);

	// BlueprintImplementableEvent:
	// Cria uma fun��o que ser� implementada na blueprint.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent,
		Category = "Sobreposicoes")
	void MyImplementableEvent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texto")
	class UTextRenderComponent* TextoDeExibicao;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
