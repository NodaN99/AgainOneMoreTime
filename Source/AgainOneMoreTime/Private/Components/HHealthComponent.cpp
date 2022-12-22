// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UHHealthComponent::UHHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHHealthComponent::OnTakeAnyDamage);
	}
}

void UHHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || bIsDead() || !GetWorld()) return;

	SetHealth(Health - Damage);

	if (bIsDead())
	{
		OnDeath.Broadcast();
	}
}

void UHHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	OnHealthChange.Broadcast(Health);
}
