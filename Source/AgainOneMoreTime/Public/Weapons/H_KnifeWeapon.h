// Horror Game, by RadoN Studio, All Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/HBaseWeaponActor.h"
#include "H_KnifeWeapon.generated.h"

class UAnimMontage;
class UBoxComponent;

UCLASS()
class AGAINONEMORETIME_API AH_KnifeWeapon : public AHBaseWeaponActor
{
	GENERATED_BODY()

public:
	AH_KnifeWeapon();

	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* AttackAnimMontage;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void MakeShot() override;

	void StartDamageTime();
	void DamageTick();
	void EndDamageTime();

	UFUNCTION()
	void MeleeMakeDamage(UPrimitiveComponent* OnComponentBeginOverlap, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void AddDamage(AActor* OtherActor, const FHitResult& SweepResult);

private:
	bool bAttackInProgress = false;
	bool bCanDamageMelee = false;
	bool bDamage = false;

	void InitAnimation();
	void OnAttackFinished(USkeletalMeshComponent* MeshComp);

	bool bCanAttack() const;
	bool bCanDamage() const;

	AH_KnifeWeapon* Knife;
};