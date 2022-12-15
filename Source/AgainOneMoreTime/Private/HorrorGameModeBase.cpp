// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorGameModeBase.h"
#include "Player/HPlayerCharacter.h"
#include "Player/HPlayerController.h"

AHorrorGameModeBase::AHorrorGameModeBase()
{
	DefaultPawnClass = AHPlayerCharacter::StaticClass();
	PlayerControllerClass = AHPlayerController::StaticClass();
}