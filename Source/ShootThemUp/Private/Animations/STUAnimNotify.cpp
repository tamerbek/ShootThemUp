// Shoot Them Up


#include "Animations/STUAnimNotify.h"
#include "STUAnimNotify.h"

void USTUAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference); 
}
