// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HPlayerCharacter.generated.h"

UCLASS()
class AGAINONEMORETIME_API AHPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent* SpringArm;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool bIsRunning() const;

private:
	bool bWantsToRun = false;
	bool bIsMovingForward = false;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void OnStartRun();
	void OnStopRun();
};
