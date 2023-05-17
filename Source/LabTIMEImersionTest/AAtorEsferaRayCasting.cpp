// 2023 Labverso, Brazil. Imersion Test.


#include "AAtorEsferaRayCasting.h"
#include "Components/BillboardComponent.h"
#include "DrawDebugHelpers.h"
#include "WorldCollision.h"

// Sets default values
AAAtorEsferaRayCasting::AAAtorEsferaRayCasting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to 
	// improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Uma Billboard � um componente que vai estar sempre apontado para a c�mera.
	// Na forma visual e de gizmo.
	UBillboardComponent* BillBoard = CreateDefaultSubobject<
		UBillboardComponent>(FName("BillBoard"));

	RootComponent = BillBoard;

	
}

// Called when the game starts or when spawned
void AAAtorEsferaRayCasting::BeginPlay()
{
	Super::BeginPlay();
	
	// Cria uma Array capaz de armazenar structs do tipo FHitResult.
	TArray<FHitResult> ColisionHitResult;

	// Obtem a localiza��o deste Ator(AAtorEsferaRaycasting)
	FVector ActorLoc = GetActorLocation();

	// Indica que a posi��o final de AAtorEsferaRaycasting seja a localiza��o
	// do Ator + 100 em x, y e z.
	FVector EndSphereRaycastDebug = ActorLoc + FVector(100, 100, 100);

	// Cria um componente de colis�o e faz ele em forma de Esfera,
	// atrav�s da fun��o MakeSphere(Radius).
	FCollisionShape ColisionSphere = FCollisionShape::MakeSphere(200.f);

	// Desenha dentro do editor do cen�rio uma representa�� visual 
	// de AAtorEsferaRaycasting. Igual ao raycast individual.
	// Custa MUITA performance.
	DrawDebugSphere(GetWorld(), ActorLoc, ColisionSphere.GetSphereRadius(),
		200, FColor::Red, true, -1.0f, (uint8)0, 0.5f);

	// Uma flag que cont�m a fun��o SweepMultiByChannel, que faz uma varredura
	// no mundo dentro da forma estabelecida(Sphere) atrav�s de uma canal de
	// colis�es e retorna todas as intera��es(overlapps e hits) encontradas.
	bool bCollisionWihSomething = GetWorld()->SweepMultiByChannel(
		ColisionHitResult, ActorLoc, EndSphereRaycastDebug, FQuat::Identity,
		ECollisionChannel::ECC_WorldStatic, ColisionSphere);

	// Se ocorrer uma intera��o dentro da varredura do SweepMultiByChannel
	// Exibir no console de logs suas informa��es.
	if (bCollisionWihSomething)
	{
		// "auto&" � utilizado para que em tempo de compila��o o tipo de 
		// colis�o(ignore, overlap e hit(block)) seja estabelecido 
		// automaticamente.
		// Como "ColisionHitResult � um array, o "for" vai varrer este array e
		// a cada elemento encontrado(colis�o realizada pelo raycast esf�rico) 
		// ele vai exibir no console de logs da Unreal.
		for (auto& Collisions : ColisionHitResult)
		{
			UE_LOG(LogTemp, Error, TEXT("Nome do Ator: %s"), 
				*Collisions.Actor->GetName());
		}
	}
}

// Called every frame
void AAAtorEsferaRayCasting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

