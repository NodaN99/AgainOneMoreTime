// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HActorComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHActorComponent::UHActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHActorComponent::BeginPlay()
{
	Super::BeginPlay();
}