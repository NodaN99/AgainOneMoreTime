// Horror Game, by RadoN Studio, All Reserved.

#include "Weapons/Melee/H_BaseMelee.h"
#include "Player/HPlayerCharacter.h"
#include "Player/HPlayerController.h"
#include "Components/BoxComponent.h"
#include "Animations/H_AttackEndAnimNotify.h"
#include "Animations/H_CanDamageAnimNotifyState.h"
#include "DrawDebugHelpers.h"

AH_BaseMelee::AH_BaseMelee()
{
	PrimaryActorTick.bCanEverTick = false;

	MeleeMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Melee Mesh");
	SetRootComponent(MeleeMesh);

	MeleeCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	MeleeCollision->SetupAttachment(MeleeMesh);

}

void AH_BaseMelee::BeginPlay()
{
	Super::BeginPlay();
}

void AH_BaseMelee::MakeAttack()
{
	const auto Character = Cast<AHPlayerCharacter>(GetOwner());
	if (!Character) return;
	
	Character->PlayAnimMontage(AttackAnimMontage);
}