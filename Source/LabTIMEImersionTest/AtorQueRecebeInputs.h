// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AtorQueRecebeInputs.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AAtorQueRecebeInputs : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAtorQueRecebeInputs();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		float Velocidade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		float VelocidadeDeRotacao;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		float Altura;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		bool bIsAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dados Adicionais")
		FName Nome;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent*
		PlayerInputComponent) override;

	UFUNCTION()
		void MovimentoVertical(float eixoVertical);

	UFUNCTION()
		void RotacaoNoEixoZ(float eixoHorizontal);

};
