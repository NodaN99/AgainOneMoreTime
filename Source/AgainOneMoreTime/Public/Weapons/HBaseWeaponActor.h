// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_CoreTypes.h"
#include "HBaseWeaponActor.generated.h"

UCLASS()
class AGAINONEMORETIME_API AHBaseWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHBaseWeaponActor();

	virtual void StartFire();
	virtual void StopFire();
	void ChangeClip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleGunSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceMaxDistance = 1500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo{15, 45};

	virtual void MakeShot();
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	APlayerController* GetPlayerController() const;
	bool GetPlayerView(FVector& ViewLocation, FRotator& ViewRotation) const;
	virtual bool GetTraceDate(FVector& TraceStart, FVector& TraceEnd);
	FVector GetMuzzleSocketName() const;

	void MakeDamage(FHitResult HitResult);

	void DecreaseAmmo();
	bool bIsAmmoEmpty();
	bool bIsClipEmpty();
	void LogAmmo();

private:
	FAmmoData CurrentAmmo;
};