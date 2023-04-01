// Horror Game, by RadoN Studio, All Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/HBaseWeaponActor.h"
#include "HRifleWeapon.generated.h"

UCLASS()
class AGAINONEMORETIME_API AHRifleWeapon : public AHBaseWeaponActor
{
	GENERATED_BODY()
	
public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimerBetweenShots = 0.1f;

	virtual void MakeShot() override;
	virtual bool GetTraceDate(FVector& TraceStart, FVector& TraceEnd) override;

private:
	FTimerHandle ShotTimerManager;

};
