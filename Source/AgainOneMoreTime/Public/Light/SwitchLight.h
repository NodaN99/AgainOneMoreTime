// Horror Game, by RadoN Studio, All Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwitchLight.generated.h"

UCLASS()
class AGAINONEMORETIME_API ASwitchLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ASwitchLight();

	void SwitchLight();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Lights")
	TArray<class APointLight*> Lights;

	virtual void BeginPlay() override;
};
