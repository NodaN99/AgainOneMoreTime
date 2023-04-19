// Horror Game, by RadoN Studio, All Reserved.

#include "Weapons/H_KnifeWeapon.h"
#include "Player/HPlayerCharacter.h"
#include "Player/HPlayerController.h"
#include "Components/BoxComponent.h"
#include "Animations/H_AttackEndAnimNotify.h"
#include "Animations/H_CanDamageAnimNotifyState.h"
#include "DrawDebugHelpers.h"
#include "Animations/AnimUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Player/H_Player.h"

DEFINE_LOG_CATEGORY_STATIC(LogHKnife, All, All);

AH_KnifeWeapon::AH_KnifeWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxCollision->SetupAttachment(WeaponMesh);
	BoxCollision->SetCollisionProfileName("NoCollision");

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AH_KnifeWeapon::MeleeMakeDamage);
}

void AH_KnifeWeapon::StartFire()
{
	MakeShot();
}

void AH_KnifeWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitAnimation();
}

void AH_KnifeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AH_KnifeWeapon::MakeShot()
{
	if (!bCanAttack()) return;
	bAttackInProgress = true;

	const auto Controller = Cast<AHPlayerController>(GetPlayerController());
	if (!Controller) return;

	const auto Character = Cast<AH_Player>(Controller->GetPawn());
	if (!Character) return;

	Character->PlayAnimMontage(AttackAnimMontage);
}

void AH_KnifeWeapon::StartDamageTime()
{
	BoxCollision->SetCollisionProfileName("Weapon");
	bCanDamageMelee = true;
	UE_LOG(LogHKnife, Display, TEXT("Damage begin is begin"));
}

void AH_KnifeWeapon::DamageTick()
{
	UE_LOG(LogHKnife, Display, TEXT("Can damage tick"));

	const auto Controller = Cast<AHPlayerController>(GetPlayerController());
	if (!Controller) return;

	const auto Character = Cast<AH_Player>(Controller->GetPawn());
	if (!Character) return;

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 10.f, 24, FColor::Silver, false, 3.f, 10.f);
}

void AH_KnifeWeapon::EndDamageTime()
{
	BoxCollision->SetCollisionProfileName("NoCollision");
	bCanDamageMelee = false;
	UE_LOG(LogHKnife, Display, TEXT("Damage end is end"));
}

void AH_KnifeWeapon::MeleeMakeDamage(UPrimitiveComponent* OnComponentBeginOverlap, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && bCanDamageMelee == true)
	{
		UE_LOG(LogHKnife, Display, TEXT("Knife is overlapping"));
		AddDamage(OtherActor, SweepResult);
	}
}

void AH_KnifeWeapon::AddDamage(AActor* OtherActor, const FHitResult& SweepResult)
{
	const auto Controller = Cast<AHPlayerController>(GetPlayerController());
	if (!Controller) return;

	const auto Character = Cast<AH_Player>(Controller->GetPawn());
	if (!Character) return;

	if (SweepResult.Actor->IsA<APawn>() && !SweepResult.Actor->IsA<AH_Player>())
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, Controller, Character, UDamageType::StaticClass());
	}
}

void AH_KnifeWeapon::InitAnimation()
{
	auto AttackFinishedNotify = AnimUtils::FindFirstNotifyByClass<UH_AttackEndAnimNotify>(AttackAnimMontage);
	if (AttackFinishedNotify)
	{
		AttackFinishedNotify->OnNotified.AddUObject(this, &AH_KnifeWeapon::OnAttackFinished);
	}
	else
	{
		UE_LOG(LogHKnife, Error, TEXT("Attack finished notify is forget to set"));
	}

	auto CanDamageNotify = AnimUtils::FindFirstNotifyStateByClass<UH_CanDamageAnimNotifyState>(AttackAnimMontage);
	if (CanDamageNotify)
	{
		CanDamageNotify->OnBeginDamageNotify.AddUObject(this, &AH_KnifeWeapon::StartDamageTime);
		CanDamageNotify->TickDamageNotify.AddUObject(this, &AH_KnifeWeapon::DamageTick);
		CanDamageNotify->OnEndDamageNotify.AddUObject(this, &AH_KnifeWeapon::EndDamageTime);
	}
	else
	{
		UE_LOG(LogHKnife, Error, TEXT("Can damage notify is forget to set"));
	}
}

void AH_KnifeWeapon::OnAttackFinished(USkeletalMeshComponent* MeshComp)
{
	const auto Controller = Cast<AHPlayerController>(GetPlayerController());
	if (!Controller) return;

	const auto Character = Cast<AH_Player>(Controller->GetPawn());
	if (!Character || MeshComp != Character->GetMesh()) return;

	UE_LOG(LogHKnife, Display, TEXT("Attack finished"));

	bAttackInProgress = false;
}

bool AH_KnifeWeapon::bCanAttack() const
{
	return !bAttackInProgress;
}

bool AH_KnifeWeapon::bCanDamage() const
{
	return !bCanDamageMelee;
}