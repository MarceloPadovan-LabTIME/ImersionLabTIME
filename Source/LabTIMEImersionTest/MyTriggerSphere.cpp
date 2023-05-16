// 2023 Labverso, Brazil. Imersion Test.

#include "MyTriggerSphere.h"
#include "Engine/Engine.h"


void AMyTriggerSphere::BeginPlay()
{
	Super::BeginPlay();


	// A Fun��o OnActorBeginOverlap � uma delegate.
	// Assim ela permite que outras fun��es possam ser anexadas a ela,
	// logo quando o evento de overlap ocorrer a fun��o OnActorBeginOverlap 
	// vai ser executada, e todas as outras fun��es que tiverem sidos anexadas 
	// via delegate.
	// Para anexar uma fun��o basta passar o endere�o da fun��o com "&"
	// this, indica que este objeto seja considerado ao anexar.
	// Ou seja, se espera que neste objeto(this), ocorra o evento overlap
	// E ele chame a fun��o "OnActorBeginOverlap", que por sua vez, vai chamar
	// a fun��o "ColisaoDetectada".
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerSphere::ColisaoDetectada);


	OnActorEndOverlap.AddDynamic(this, &AMyTriggerSphere::FimColisao);

}

void AMyTriggerSphere::ColisaoDetectada(AActor* me, AActor* other)
{
	// Quando algum objeto/ator colidir com o Trigger,
	// uma mensagem ser� exibida na tela.
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(
		TEXT("Entrou no Trigger Loc: %s"), *GetActorLocation().ToString()));
	
	// Quando algum objeto/ator colidir com o Trigger, ser� destu�do.
	// other->Destroy();
}

void AMyTriggerSphere::FimColisao(AActor* me, AActor* other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Saiu do Trigger Loc: %s"), *GetActorLocation().ToString()));
}
