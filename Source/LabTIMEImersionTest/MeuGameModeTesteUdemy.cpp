// 2023 Labverso, Brazil. Imersion Test.


// Includes necessarios para utilização de diversos recursos 
// e classes no código.
// Indica ao Compilador onde ele vai encontrar as funções e classes utilizados
// e quando realizar os links.
#include "MeuGameModeTesteUdemy.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "AGranade.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


// Game mode é uma classe que contém as regras e configurações do nosso jogo.
// Cada level pode ter seu próprio GameMode.
// Para isso em World Settings você pode sobrescrever o GameMode padrão.
void AMeuGameModeTesteUdemy::BeginPlay()
{
	Super::BeginPlay();

	// Cria uma variavel do tipo Array Dinâmico capaz de armazenar 
	// ponteiros(Endereços de memória) do tipo AActor ou subclasses de AActor.
	UPROPERTY()
	TArray<AActor*> LocalGranades;

	// Uma função que vai procurar no mundo todas as Target Point
	// e para cada um encontrado, irá adicionar no 
	// array dinâmico "LocalGranades" seu respectivo endereço de memória.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), 
		ATargetPoint::StaticClass(), LocalGranades);

	UE_LOG(LogTemp, Warning, TEXT("Num de Target Point Encontrados:  %d"),
		LocalGranades.Num());

	if (LocalGranades.Num() != 0)
	{
		// FActorSpawnParamets são configurações adicionais para quando se cria
		// um ator via função SpawnActor.
		FActorSpawnParameters params = FActorSpawnParameters();
		for (auto It : LocalGranades)
		{
			GetWorld()->SpawnActor<AAGranade>(It->GetActorLocation(),
				It->GetActorRotation(), params);

			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, TEXT(
				"Ator Gerado"));

			UE_LOG(LogTemp, Warning, TEXT("Transform = %s"), 
				*It->GetActorLocation().ToString());

		}
	}

}

