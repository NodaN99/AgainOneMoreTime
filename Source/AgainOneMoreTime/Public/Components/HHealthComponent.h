// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float)
DECLARE_MULTICAST_DELEGATE(FOnDeathCharacter)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGAINONEMORETIME_API UHHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHHealthComponent();

	float GetHeath() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool bIsDead() const { return FMath::IsNearlyZero(Health); }

	FOnDeathCharacter OnDeath;
	FOnHealthChange OnHealthChange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MaxHealth = 100.f;

private:
	float Health = 0.f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void SetHealth(float NewHealth);
<<<<<<< HEAD
};
=======
};
>>>>>>> origin/RaDick
