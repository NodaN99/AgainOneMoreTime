// Horror Game, by RadoN Studio, All Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwitchLight.generated.h"

class UStaticMeshComponent;
class APointLight;

UCLASS()
class AGAINONEMORETIME_API ASwitchLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ASwitchLight();

	void SwitchLight();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Lights")
	TArray<APointLight*> Lights;

	virtual void BeginPlay() override;
};
