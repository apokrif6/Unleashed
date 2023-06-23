// Unleashed


#include "Equipment/Weapon/Weapon.h"
#include "Interfaces/AnimInstanceInterface.h"
#include "Unleashed/UnleashedCharacter.h"

void AWeapon::Equip()
{
	SetIsEquipped(true);

	const AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(Owner);
	if (!UnleashedCharacter) return;

	if (UnleashedCharacter->GetCombatComponent()->GetInCombatMode())
	{
		AttachActorToOwner(HandAttachSocketName);
	}
	else
	{
		AttachActorToOwner(AttachSocketName);
	}

	UnleashedCharacter->GetCombatComponent()->SetMainWeapon(this);

	UnleashedCharacter->GetCombatComponent()->ResetAttackCount();

	if (UnleashedCharacter->GetMesh()->GetAnimInstance()->Implements<UAnimInstanceInterface>())
	{
		IAnimInstanceInterface::Execute_ChangeCombatStyle(UnleashedCharacter->GetMesh()->GetAnimInstance(),
		                                                  CombatStyle);
	}
}
