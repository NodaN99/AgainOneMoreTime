// Horror Game, by RadoN Studio, All Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/HBaseWeaponActor.h"
#include "HPistolWeapon.generated.h"

UCLASS()
class AGAINONEMORETIME_API AHPistolWeapon : public AHBaseWeaponActor
{
	GENERATED_BODY()
	
public:
	virtual void StartFire() override;

protected:
	virtual void MakeShot() override;
};
