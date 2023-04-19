// Horror Game, by RadoN Studio, All Reserved.

#include "Weapons/HRifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogRifleWeapon, All, All)

void AHRifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerManager, this, &AHRifleWeapon::MakeShot, TimerBetweenShots, true);
	MakeShot();
}

void AHRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerManager);
}

void AHRifleWeapon::MakeShot()
{
	if (!GetWorld() || bIsClipEmpty() || bIsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceDate(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleSocketName(), HitResult.ImpactPoint, FColor::Green, false, 3.f, 0, 2.f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 12.f, 24, FColor::Red, false, 3.f, 0, 2.f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleSocketName(), TraceEnd, FColor::Green, false, 3.f, 0, 2.f);
	}
	DecreaseAmmo();
}

bool AHRifleWeapon::GetTraceDate(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerView(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShotDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShotDirection * TraceMaxDistance;
	return true;
}