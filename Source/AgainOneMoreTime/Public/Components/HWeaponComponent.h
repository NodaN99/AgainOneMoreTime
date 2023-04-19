// Horror Game, by RadoN Studio, All Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HWeaponComponent.generated.h"

class AHBaseWeaponActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGAINONEMORETIME_API UHWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHWeaponComponent();

	void StartFire();
	void StopFire();
	void Reload();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AHBaseWeaponActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName GunSocketName = "GunSocket";

	virtual void BeginPlay() override;

	void ChangeClip();

private:
	UPROPERTY()
	AHBaseWeaponActor* CurrentWeapon;

	void SpawnWeapon();
	void AttachWeaponToSocket(AHBaseWeaponActor* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
};