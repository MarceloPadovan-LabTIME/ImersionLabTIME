// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AInsertGranades.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AAInsertGranades : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAInsertGranades();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	 class USphereComponent* ColisorDoAtor;

	 // Propriedade visivel no editor que vai permitir indicar qual a classe 
	 // que o o objeto pertence.
	 // Contudo, a escolha desta classe será limitada por 
	 // TSubclassOf(Subclasse de).
	 // Classe Granade e suas Subclasses FireGranade e SmokeGranade.
	 UPROPERTY(EditAnywhere, Category = "Tipo de Granada")
	 TSubclassOf<class AAGranade> BpGranade;

};
