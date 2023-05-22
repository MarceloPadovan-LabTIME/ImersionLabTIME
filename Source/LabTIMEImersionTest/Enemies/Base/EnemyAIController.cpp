// 2023 Labverso, Brazil. Imersion Test.


#include "EnemyAIController.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "EnemyCharacterBase.h"
#include "Engine/Engine.h"
#include "LabTIMEImersionTest/Weapons/Base/WeaponBase.h"

/* Constructor */
AEnemyAIController::AEnemyAIController()
{
	/* Create sensors(FieldOfView) component of the EnemyCharacter */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(
		FName("PawnSensingComp"));
	/* Configuration of Enemy`s Field of View/Line of Sight Behavior */
	PawnSensingComp->SensingInterval = 0.25f;
	PawnSensingComp->bOnlySensePlayers = true;
	PawnSensingComp->SetPeripheralVisionAngle(180.0f);
	PawnSensingComp->SightRadius = 1000.0f;

	/* Create the BehaviorTree component to manipulate the IA */
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(
		FName("BehaviorTreeComp"));

	/* Create the Blackborad component */
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(
		FName("BlackboardComp"));

}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	/* Binding OnSeePawn delegate function, when the enemy SensingComp 
	see the Player Actor */
	PawnSensingComp->OnSeePawn.AddDynamic(
		this, &AEnemyAIController::OnSeePawn);

	if (BehaviorTree)
	{
		/* Initiate the Blackborad and BehaviorTree */
		BlackBoardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);

		/* Now the EnemyIA start patrolling looking for the Player */
		BlackBoardComp->SetValueAsBool("CanPatrol", true);
	}
}

void AEnemyAIController::OnSeePawn(APawn* SensedPawn)
{
	/* Check if the Blackboard is On, and if the Enemy see the Player */
	if (BlackBoardComp && SensedPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f,
			FColor::Red, TEXT("Você está sendo visto!"));
		/* 
		* Ensures that the EnemyAI see the Player, 
		* Get/Set the player actor as "SightedPlayer" object,
		* and will no longer patrol.
		*/
		BlackBoardComp->SetValueAsObject("SightedPlayer", SensedPawn);
		BlackBoardComp->SetValueAsBool("CanPatrol", false);

		/* 
		* A Reference of the enemy actor, that is being controlled 
		* by this Controller.
		* "Cast" transform the APawn return into a AEnemyCharacterBase.
		*/
		AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(GetPawn());

		/* When the Enemy see the player, He will shot */
		Enemy->EnemyWeapon->FireWeapon();
	}
}
