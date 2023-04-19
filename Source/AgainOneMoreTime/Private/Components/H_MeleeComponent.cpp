// Horror Game, by RadoN Studio, All Reserved.

#include "Components/H_MeleeComponent.h"

UH_MeleeComponent::UH_MeleeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UH_MeleeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UH_MeleeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}