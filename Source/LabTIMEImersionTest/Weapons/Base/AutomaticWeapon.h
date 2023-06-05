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
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

public:
	/** 
	* Fires the automatic weapon. 
	* In this case, if the player holds the mouse buttom, 
	* the weapon will keep firing until we have no ammo left.
	*/
	virtual void FireWeapon() override;

	/** 
	* When release the fire buttom, this function is called to reset the
	* TimerHandle and SpreadValue.
	*/
	virtual void StopFiringWeapon() override;

	/** This function will be called to return corsshair to defaults
	configutation after consecultives shots, making a smoothed return */
	void SmoothCrosshairReturn();


private:
	/* The Timer Handle for Consecultive shots */
	FTimerHandle ShootTimerHandle;

	/* The Timer Handle for smooth crosshair reset */
	FTimerHandle SmoothCrosshairTimeHandle;
};
