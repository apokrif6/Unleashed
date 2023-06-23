// Unleashed


#include "AnimNotifies/CancelComboNotify.h"

#include "Unleashed/UnleashedCharacter.h"

void UCancelComboNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	AUnleashedCharacter* WeaponOwner = Cast<AUnleashedCharacter>(MeshComp->GetOwner());

	if (!WeaponOwner) return;

	WeaponOwner->CancelCombo();
}
