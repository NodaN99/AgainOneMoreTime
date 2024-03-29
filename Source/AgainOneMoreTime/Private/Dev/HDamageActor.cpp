// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/HDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHDamageActor::AHDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	SetRootComponent(SceneComp);
}

// Called when the game starts or when spawned
void AHDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Draw damage sphere
	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, bDoFullDamage);
}