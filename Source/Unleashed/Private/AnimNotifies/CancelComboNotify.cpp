// Unleashed


#include "AnimNotifies/CancelComboNotify.h"

#include "Unleashed/UnleashedCharacter.h"

void UCancelComboNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(MeshComp->GetOwner());

	if (!UnleashedCharacter) return;

	UnleashedCharacter->CancelCombo();
}
