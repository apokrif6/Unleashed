// Unleashed


#include "AnimNotifies/ResetRollNotify.h"
#include "Unleashed/UnleashedCharacter.h"

void UResetRollNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                              const FAnimNotifyEventReference& EventReference)
{
	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(MeshComp->GetOwner());

	if (!UnleashedCharacter) return;

	UnleashedCharacter->ResetRoll();
}
