// Horror Game, by RadoN Studio, All Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_BaseMelee.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class UAnimMontage;

UCLASS()
class AGAINONEMORETIME_API AH_BaseMelee : public AActor
{
	GENERATED_BODY()
	
public:
	AH_BaseMelee();

	virtual void StartFire() {};
	virtual void StopFire() {};

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	USkeletalMeshComponent* MeleeMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	UBoxComponent* MeleeCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* AttackAnimMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Melee")
	FName MuzzleSocketName = "MuzzleGunSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Melee")
	float Damage = 20.f;

	virtual void BeginPlay() override;

	void MakeAttack();
};