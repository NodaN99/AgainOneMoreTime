// Horror Game, by RadoN Studio, All Reserved.


#include "Light/SwitchLight.h"
#include "Components/StaticMeshComponent.h"
#include "Weapons/HBaseWeaponActor.h"

// Sets default values
ASwitchLight::ASwitchLight()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
}

void ASwitchLight::BeginPlay()
{
	Super::BeginPlay();
}

void ASwitchLight::SwitchLight()
{
}