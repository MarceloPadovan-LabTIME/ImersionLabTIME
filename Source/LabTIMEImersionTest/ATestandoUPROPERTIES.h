// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATestandoUPROPERTIES.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AATestandoUPROPERTIES : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATestandoUPROPERTIES();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditDefaultsOnly, Category = "Especificadores")
	int32 EditDefaultsOnly;

	UPROPERTY(EditInstanceOnly, Category = "Especificadores")
    int32 EditInstanceOnly;

	UPROPERTY(EditAnywhere, Category = "Especificadores")
	int32 EditAnywhere;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
