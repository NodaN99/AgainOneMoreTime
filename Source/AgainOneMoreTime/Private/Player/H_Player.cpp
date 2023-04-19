// Horror Game, by RadoN Studio, All Reserved.

#include "Player/H_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/HWeaponComponent.h"
#include "GameFramework/Controller.h"

AH_Player::AH_Player(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void AH_Player::BeginPlay()
{
	Super::BeginPlay();
}

void AH_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//check(SwitchLight);

	//Binding axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AH_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AH_Player::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AHPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AHPlayerCharacter::AddControllerPitchInput);

	//Binding action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AH_Player::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AH_Player::OnStopRun);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UHWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UHWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UHWeaponComponent::Reload);
}

void AH_Player::MoveForward(float Value)
{
	if (Value == 0.f) return;
	bIsMovingForward = Value > 0.f;
	AddMovementInput(GetActorForwardVector(), Value);
}

void AH_Player::MoveRight(float Value)
{
	if (Value == 0.f) return;
	AddMovementInput(GetActorRightVector(), Value);
}

void AH_Player::OnStartRun()
{
	bWantsToRun = true;
}

void AH_Player::OnStopRun()
{
	bWantsToRun = false;
}

//Caling when charcter IsRunning
bool AH_Player::bIsRunning() const
{
	return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
}

void AH_Player::OnDeath()
{
	Super::OnDeath();
}