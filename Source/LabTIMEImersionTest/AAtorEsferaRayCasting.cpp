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


	// Uma Billboard é um componente que vai estar sempre apontado para a câmera.
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

	// Obtem a localização deste Ator(AAtorEsferaRaycasting)
	FVector ActorLoc = GetActorLocation();

	// Indica que a posição final de AAtorEsferaRaycasting seja a localização
	// do Ator + 100 em x, y e z.
	FVector EndSphereRaycastDebug = ActorLoc + FVector(100, 100, 100);

	// Cria um componente de colisão e faz ele em forma de Esfera,
	// através da função MakeSphere(Radius).
	FCollisionShape ColisionSphere = FCollisionShape::MakeSphere(200.f);

	// Desenha dentro do editor do cenário uma representaçã visual 
	// de AAtorEsferaRaycasting. Igual ao raycast individual.
	// Custa MUITA performance.
	DrawDebugSphere(GetWorld(), ActorLoc, ColisionSphere.GetSphereRadius(),
		200, FColor::Red, true, -1.0f, (uint8)0, 0.5f);

	// Uma flag que contém a função SweepMultiByChannel, que faz uma varredura
	// no mundo dentro da forma estabelecida(Sphere) através de uma canal de
	// colisões e retorna todas as interações(overlapps e hits) encontradas.
	bool bCollisionWihSomething = GetWorld()->SweepMultiByChannel(
		ColisionHitResult, ActorLoc, EndSphereRaycastDebug, FQuat::Identity,
		ECollisionChannel::ECC_WorldStatic, ColisionSphere);

	// Se ocorrer uma interação dentro da varredura do SweepMultiByChannel
	// Exibir no console de logs suas informações.
	if (bCollisionWihSomething)
	{
		// "auto&" é utilizado para que em tempo de compilação o tipo de 
		// colisão(ignore, overlap e hit(block)) seja estabelecido 
		// automaticamente.
		// Como "ColisionHitResult é um array, o "for" vai varrer este array e
		// a cada elemento encontrado(colisão realizada pelo raycast esférico) 
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

