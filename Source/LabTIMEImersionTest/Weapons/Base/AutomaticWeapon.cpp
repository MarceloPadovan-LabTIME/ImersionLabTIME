// 2023 Labverso, Brazil. Imersion Test.


#include "AutomaticWeapon.h"
#include "LabTIMEImersionTest/MainPlayer/MainPlayerCharacter.h"

void AAutomaticWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAutomaticWeapon::FireWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("PEW from automatic weapon!"));

	if (WeaponCurrentAmmunitionAmount > 0 && !bIsWeaponReloading)
	{
		// Make one shot.
		WeaponShot();

		GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this,
			&AAutomaticWeapon::FireWeapon, ShotInterval, true);

		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Stopping fully auto fire, after else."));
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	Reload();
}

void AAutomaticWeapon::StopFiringWeapon()
{
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	

	GetWorld()->GetTimerManager().SetTimer(SmoothCrosshairTimeHandle, this,
		&AAutomaticWeapon::SmoothCrosshairReturn,
		SmoothCrosshairInterval, true);
}

void AAutomaticWeapon::SmoothCrosshairReturn()
{
	WeaponSpreadCurrentValue -= 1.0f;
	if (WeaponSpreadCurrentValue <= 0)
	{
		GetWorldTimerManager().ClearTimer(SmoothCrosshairTimeHandle);
		WeaponSpreadCurrentValue = 0.0f;
		UE_LOG(LogTemp, Error, TEXT("Weapon Spread: %f"), WeaponSpreadCurrentValue);
	}
}
