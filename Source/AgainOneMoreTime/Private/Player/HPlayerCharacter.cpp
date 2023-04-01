// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HPlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/MyCharacterMovementComponent.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> origin/RaDick
#include "Components/HHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Weapons/HBaseWeaponActor.h"
#include "Components/HWeaponComponent.h"
#include "Light/SwitchLight.h"

DEFINE_LOG_CATEGORY_STATIC(LogHCharacter, All, All)
<<<<<<< HEAD
>>>>>>> origin/master
=======
>>>>>>> origin/RaDick

// Sets default values
AHPlayerCharacter::AHPlayerCharacter(const FObjectInitializer& ObjInit) 
	: Super(ObjInit.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComp");
	HealthTextComponent->SetupAttachment(GetRootComponent());

	WeaponComponent = CreateDefaultSubobject<UHWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void AHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);

<<<<<<< HEAD
	//Connect to delegates
=======
>>>>>>> origin/RaDick
	OnHealthChange(HealthComponent->GetHeath());
	HealthComponent->OnDeath.AddUObject(this, &AHPlayerCharacter::OnDeath);
	HealthComponent->OnHealthChange.AddUObject(this, &AHPlayerCharacter::OnHealthChange);
}

// Called every frame
void AHPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Health = HealthComponent->GetHeath();
}

// Called to bind functionality to input
void AHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);
	check(SwitchLight);

	//Binding axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AHPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AHPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AHPlayerCharacter::AddControllerPitchInput);

	//Binding action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AHPlayerCharacter::OnStopRun);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UHWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UHWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UHWeaponComponent::Reload);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, SwitchLight, &ASwitchLight::SwitchLight);
}

void AHPlayerCharacter::MoveForward(float Value)
{
	if (Value == 0.f) return;
	bIsMovingForward = Value > 0.f;
	AddMovementInput(GetActorForwardVector(), Value);
}

void AHPlayerCharacter::MoveRight(float Value)
{
	if (Value == 0.f) return;
	AddMovementInput(GetActorRightVector(), Value);
}

void AHPlayerCharacter::OnStartRun()
{
	bWantsToRun = true;
}

void AHPlayerCharacter::OnStopRun()
{
	bWantsToRun = false;
}

<<<<<<< HEAD
<<<<<<< HEAD
bool AHPlayerCharacter::bIsRunning() const
{
	return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
=======
//Caling when charcter IsRunning
bool AHPlayerCharacter::bIsRunning() const
{
	return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
=======
//Caling when charcter IsRunning
bool AHPlayerCharacter::bIsRunning() const
{
	return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
>>>>>>> origin/RaDick
}

//Caling when character death
void AHPlayerCharacter::OnDeath()
{
	UE_LOG(LogHCharacter, Display, TEXT("Character id dead"));

	PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	/*APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	DisableInput(PlayerController);*/
}

//Caling when health change
void AHPlayerCharacter::OnHealthChange(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
<<<<<<< HEAD
>>>>>>> origin/master
=======
>>>>>>> origin/RaDick
}