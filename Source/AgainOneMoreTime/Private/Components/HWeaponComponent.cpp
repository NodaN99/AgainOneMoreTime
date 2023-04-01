// Horror Game, by RadoN Studio, All Reserved.

#include "Components/HWeaponComponent.h"
#include "Weapons/HBaseWeaponActor.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UHWeaponComponent::UHWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UHWeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void UHWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void UHWeaponComponent::Reload()
{
	ChangeClip();
}

void UHWeaponComponent::ChangeClip()
{
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
}

void UHWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<AHBaseWeaponActor>(WeaponClass);
	if (!CurrentWeapon) return;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), GunSocketName);
}

void UHWeaponComponent::AttachWeaponToSocket(AHBaseWeaponActor* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}