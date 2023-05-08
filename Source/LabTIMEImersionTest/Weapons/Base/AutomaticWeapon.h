// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "AutomaticWeapon.generated.h"

/**
* This class inherits from AWeaponBase and adds the functionality
* of automatic weapons.
* Automatic weapons are those that will keep firing as long as the
* player keeps the fire input pressed.
* 
* @see AWeaponBase
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AAutomaticWeapon : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	/** 
	* Fires the automatic weapon. 
	* In this case, if the player holds the mouse buttom, 
	* the weapon will keep firing until we have no ammo left.
	*/
	virtual void FireWeapon() override;
};
