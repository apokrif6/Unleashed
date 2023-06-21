// Unleashed


#include "Equipment/Weapon/Weapon.h"
#include "Interfaces/AnimInstanceInterface.h"
#include "Unleashed/UnleashedCharacter.h"

void AWeapon::Equip()
{
	SetIsEquipped(true);

	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(Owner);
	if (!UnleashedCharacter) return;

	if (UnleashedCharacter->GetInCombatMode())
	{
		AttachActorToOwner(HandAttachSocketName);
	}
	else
	{
		AttachActorToOwner(AttachSocketName);
	}

	UnleashedCharacter->SetWeapon(this);

	if (UnleashedCharacter->GetMesh()->GetAnimInstance()->Implements<UAnimInstanceInterface>())
	{
		IAnimInstanceInterface::Execute_ChangeCombatStyle(UnleashedCharacter->GetMesh()->GetAnimInstance(),
		                                                  CombatStyle);
	}
}
