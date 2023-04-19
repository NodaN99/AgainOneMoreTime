// Horror Game, by RadoN Studio, All Reserved.

#include "Animations/H_AttackEndAnimNotify.h"

void UH_AttackEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}