// Unleashed


#include "AnimNotifies/AttachWeaponNotify.h"
#include "Unleashed/UnleashedCharacter.h"

void UAttachWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                 const FAnimNotifyEventReference& EventReference)
{
	AUnleashedCharacter* WeaponOwner = Cast<AUnleashedCharacter>(MeshComp->GetOwner());

	if (!WeaponOwner) return;

	WeaponOwner->GetCombatComponent()->AttachWeapon(bAttachToHand);
}
