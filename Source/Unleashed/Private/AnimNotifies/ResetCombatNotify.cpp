// Unleashed


#include "AnimNotifies/ResetCombatNotify.h"
#include "Unleashed/UnleashedCharacter.h"

void UResetCombatNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(MeshComp->GetOwner());

	if (!UnleashedCharacter) return;

	UnleashedCharacter->ResetCombat();
}
