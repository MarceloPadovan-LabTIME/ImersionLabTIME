// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterBase.generated.h"

/** 
* This is the enemie's base character class. 
* This class deals with the base functionality of a enemy, e.g., it's movement.
* Extend this class for futher base functionalities.
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	/** Sets default values for this character's properties */
	AEnemyCharacterBase();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	class AWeaponBase* EnemyWeapon;

public: 

	UFUNCTION()
		void SetHealth(float Damage);

	UFUNCTION()
		float GetHealth();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/* Let`s give a weapon to the enemy, like player */
	UPROPERTY(EditAnyWhere, Category = "Weapon")
	TSubclassOf<class AWeaponBase> BP_Weapon_AssaultRifle;

	/* Enemy main atribute, the health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Atributos")
	float Health;
	/* A flag to check if the enemy still alive or not */
	UPROPERTY(BlueprintReadOnly, Category = "Atibutos")
	bool bIsDead;

};
