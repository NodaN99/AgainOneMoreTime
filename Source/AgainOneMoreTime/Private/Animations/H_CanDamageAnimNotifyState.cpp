// Horror Game, by RadoN Studio, All Reserved.

#include "Animations/H_CanDamageAnimNotifyState.h"

void UH_CanDamageAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	OnBeginDamageNotify.Broadcast();
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
}

void UH_CanDamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	TickDamageNotify.Broadcast();
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UH_CanDamageAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnEndDamageNotify.Broadcast();
	Super::NotifyEnd(MeshComp, Animation);
}