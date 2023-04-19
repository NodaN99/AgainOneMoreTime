// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/HPlayerCharacter.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Components/HHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Components/HWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Light/SwitchLight.h"

DEFINE_LOG_CATEGORY_STATIC(LogHCharacter, All, All)

// Sets default values
AHPlayerCharacter::AHPlayerCharacter(const FObjectInitializer& ObjInit) 
	: Super(ObjInit.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

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

	//Connect to delegates
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

bool AHPlayerCharacter::bIsRunning() const
{
	return false;
}

float AHPlayerCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

//Caling when character death
void AHPlayerCharacter::OnDeath()
{
	UE_LOG(LogHCharacter, Display, TEXT("Character id dead"));

	GetCharacterMovement()->DisableMovement();

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

//Caling when health change
void AHPlayerCharacter::OnHealthChange(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}