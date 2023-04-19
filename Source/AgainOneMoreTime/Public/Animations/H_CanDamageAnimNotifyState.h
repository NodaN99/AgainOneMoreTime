// Horror Game, by RadoN Studio, All Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "H_CanDamageAnimNotifyState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnBeginNotifySignature);
DECLARE_MULTICAST_DELEGATE(FOnTickNotifySignature);
DECLARE_MULTICAST_DELEGATE(FOnEndNotifySignature);

UCLASS()
class AGAINONEMORETIME_API UH_CanDamageAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FOnBeginNotifySignature OnBeginDamageNotify;
	FOnTickNotifySignature TickDamageNotify;
	FOnEndNotifySignature OnEndDamageNotify;
};