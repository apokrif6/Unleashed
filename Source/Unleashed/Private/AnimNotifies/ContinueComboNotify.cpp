// Unleashed


#include "AnimNotifies/ContinueComboNotify.h"

#include "Unleashed/UnleashedCharacter.h"

void UContinueComboNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	AUnleashedCharacter* WeaponOwner = Cast<AUnleashedCharacter>(MeshComp->GetOwner());

	if (!WeaponOwner) return;

	WeaponOwner->ContinueCombo();
}
