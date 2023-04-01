// Horror Game, by RadoN Studio, All Reserved.


#include "Weapons/HPistolWeapon.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogPistolWeapon, All, All)

void AHPistolWeapon::StartFire()
{
	MakeShot();
}

void AHPistolWeapon::MakeShot()
{
	if (!GetWorld() || bIsClipEmpty() || bIsAmmoEmpty())
	{
		StopFire();
		return;
	}

	Super::MakeShot();
	DecreaseAmmo();
}