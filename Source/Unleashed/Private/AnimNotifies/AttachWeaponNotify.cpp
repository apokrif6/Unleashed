// Unleashed


#include "AnimNotifies/AttachWeaponNotify.h"
#include "Unleashed/UnleashedCharacter.h"

void UAttachWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                 const FAnimNotifyEventReference& EventReference)
{
	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(MeshComp->GetOwner());

	if (!UnleashedCharacter) return;

	UnleashedCharacter->GetCombatComponent()->AttachWeapon(bAttachToHand);
}
