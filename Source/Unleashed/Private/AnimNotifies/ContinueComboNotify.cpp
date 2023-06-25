// Unleashed


#include "AnimNotifies/ContinueComboNotify.h"
#include "Unleashed/UnleashedCharacter.h"

void UContinueComboNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(MeshComp->GetOwner());

	if (!UnleashedCharacter) return;

	UnleashedCharacter->ContinueCombo();
}
