// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
* This is the enemie's AI controller class.
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	AEnemyAIController();

	/** 
	* Gives the control of the Enemy Pawn(Enemy Character)
	* to the AIController(this class). 
	*/
	virtual void OnPossess(APawn* InPawn) override;

	/** Create sensory functionalities(vision, audition) of an actor */
	UPROPERTY(EditDefaultsOnly)
	class UPawnSensingComponent* PawnSensingComp;

	/** A Reference of the Enemy A.I. Behavior Tree */
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	/** Create a Behavior Tree Component, to use its features */
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	/** Create a Blackboard Component, to use its features */
	UPROPERTY(EditDefaultsOnly)
	class UBlackboardComponent* BlackBoardComp;

	/** Delegate function, will be called when the enemyAI see the player */
	UFUNCTION()
	void OnSeePawn(class APawn* SensedPawn);

};
