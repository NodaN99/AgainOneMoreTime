// Horror Game, by RadoN Studio, All Reserved.

#include "Light/SwitchLight.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/PointLight.h"
#include "Components/PointLightComponent.h"

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
	//const auto Controller = GetWorld()->GetFirstPlayerController();
	//if (!Controller) return;

	//const auto Player = Controller->GetPawn();
	//if (!Player) return;
	//
	///*FVector Location;
	//FRotator Rotation;
	//Player->GetActorEyesViewPoint(Location, Rotation);*/

	for (auto Light : Lights)
	{
		const auto AllLights = Cast<UPointLightComponent>(Light);
		AllLights->SetLightBrightness(0.f);
	}
}