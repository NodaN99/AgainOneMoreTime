// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HPlayerCharacter.generated.h"

class UHHealthComponent;
class UTextRenderComponent;
class UHWeaponComponent;
class USceneComponent;

UCLASS()
class AGAINONEMORETIME_API AHPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHPlayerCharacter(const FObjectInitializer& ObjInit);

	virtual void Tick(float DeltaTime) override;

	//Function for run
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool bIsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHWeaponComponent* WeaponComponent;

	virtual void BeginPlay() override;

	//Void for health
	virtual void OnDeath();
	virtual void OnHealthChange(float Health);

private:
	
};