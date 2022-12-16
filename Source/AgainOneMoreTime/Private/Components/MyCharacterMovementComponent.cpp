// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Player/HPlayerCharacter.h"

float UMyCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const AHPlayerCharacter* Player = Cast<AHPlayerCharacter>(GetPawnOwner());
    return Player && Player->bIsRunning() ? MaxSpeed * RunModifire : MaxSpeed;
}