// 2023 Labverso, Brazil. Imersion Test.


// Includes necessarios para utiliza��o de diversos recursos 
// e classes no c�digo.
// Indica ao Compilador onde ele vai encontrar as fun��es e classes utilizados
// e quando realizar os links.
#include "MeuGameModeTesteUdemy.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "AGranade.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


// Game mode � uma classe que cont�m as regras e configura��es do nosso jogo.
// Cada level pode ter seu pr�prio GameMode.
// Para isso em World Settings voc� pode sobrescrever o GameMode padr�o.
void AMeuGameModeTesteUdemy::BeginPlay()
{
	Super::BeginPlay();

	// Cria uma variavel do tipo Array Din�mico capaz de armazenar 
	// ponteiros(Endere�os de mem�ria) do tipo AActor ou subclasses de AActor.
	UPROPERTY()
	TArray<AActor*> LocalGranades;

	// Uma fun��o que vai procurar no mundo todas as Target Point
	// e para cada um encontrado, ir� adicionar no 
	// array din�mico "LocalGranades" seu respectivo endere�o de mem�ria.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), 
		ATargetPoint::StaticClass(), LocalGranades);

	UE_LOG(LogTemp, Warning, TEXT("Num de Target Point Encontrados:  %d"),
		LocalGranades.Num());

	if (LocalGranades.Num() != 0)
	{
		// FActorSpawnParamets s�o configura��es adicionais para quando se cria
		// um ator via fun��o SpawnActor.
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

