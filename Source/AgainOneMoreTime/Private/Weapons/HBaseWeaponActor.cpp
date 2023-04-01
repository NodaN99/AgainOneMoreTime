// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HBaseWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

AHBaseWeaponActor::AHBaseWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

void AHBaseWeaponActor::StartFire() {}

void AHBaseWeaponActor::StopFire() {}

void AHBaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = DefaultAmmo;
}

void AHBaseWeaponActor::MakeShot()
{
	FVector TraceStart, TraceEnd;
	if (!GetTraceDate(TraceStart, TraceEnd)) return;

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
}

void AHBaseWeaponActor::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

APlayerController* AHBaseWeaponActor::GetPlayerController() const
{
	const auto Player = GetWorld()->GetFirstPlayerController();
	if (!Player) return nullptr;

	return Player;
}

bool AHBaseWeaponActor::GetPlayerView(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

bool AHBaseWeaponActor::GetTraceDate(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerView(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const FVector ShotDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShotDirection * TraceMaxDistance;
	return true;
}

FVector AHBaseWeaponActor::GetMuzzleSocketName() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

void AHBaseWeaponActor::MakeDamage(FHitResult HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;

	DamagedActor->TakeDamage(Damage, FDamageEvent(), GetPlayerController(), this);
	UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
}

void AHBaseWeaponActor::DecreaseAmmo()
{
	LogAmmo();
	if(CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogBaseWeapon, Display, TEXT("0 bullets, need reload"));
		StopFire();
		return;
	}
	CurrentAmmo.Bullets--;
	LogAmmo();
}

//Check has ammo
bool AHBaseWeaponActor::bIsAmmoEmpty()
{
	return CurrentAmmo.MaxBullets == 0 && bIsClipEmpty();
}

//Check has clips
bool AHBaseWeaponActor::bIsClipEmpty()
{
	return CurrentAmmo.Bullets == 0;
}

void AHBaseWeaponActor::ChangeClip()
{
	if (bIsAmmoEmpty() || CurrentAmmo.Bullets == DefaultAmmo.Bullets || CurrentAmmo.MaxBullets == 0)
	{
		StopFire();
		return;
	}

	//Difference bullets Default and Current for magazine cartridge
	int32 BulletsDifference = (DefaultAmmo.Bullets - CurrentAmmo.Bullets);

	//That MaxBullet won't negative
	if (BulletsDifference > CurrentAmmo.MaxBullets)
	{
		CurrentAmmo.Bullets += CurrentAmmo.MaxBullets;
		CurrentAmmo.MaxBullets = 0;
	}
	else
	{
		CurrentAmmo.MaxBullets -= BulletsDifference;
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}
	UE_LOG(LogBaseWeapon, Display, TEXT("Reload"));
}

//Log info about bullet and clips
void AHBaseWeaponActor::LogAmmo()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Bullets: %i | MaxBullets: %i"), CurrentAmmo.Bullets, CurrentAmmo.MaxBullets);
}