// Horror Game, by RadoN Studio, All Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/HPlayerCharacter.h"
#include "H_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ASwitchLight;

UCLASS()
class AGAINONEMORETIME_API AH_Player : public AHPlayerCharacter
{
	GENERATED_BODY()
	
public:
	AH_Player(const FObjectInitializer& ObjInit);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool bIsRunning() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ASwitchLight* SwitchLights;

	virtual void BeginPlay() override;

	virtual void OnDeath() override;

private:
	//Var for run
	bool bWantsToRun = false;
	bool bIsMovingForward = false;

	//Void for move
	void MoveForward(float Value);
	void MoveRight(float Value);

	//Void for run
	void OnStartRun();
	void OnStopRun();
};
