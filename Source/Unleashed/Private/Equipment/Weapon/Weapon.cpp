// Unleashed


#include "Equipment/Weapon/Weapon.h"
#include "Interfaces/AnimInstanceInterface.h"
#include "Unleashed/UnleashedCharacter.h"

void AWeapon::Equip()
{
	Super::Equip();

	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(Owner);
	if (!UnleashedCharacter) return;

	UnleashedCharacter->SetWeapon(this);

	if (UnleashedCharacter->GetMesh()->GetAnimInstance()->Implements<UAnimInstanceInterface>())
	{
		IAnimInstanceInterface::Execute_ChangeCombatStyle(UnleashedCharacter->GetMesh()->GetAnimInstance(),
		                                                  CombatStyle);
	}
}

void AWeapon::SetAttachedToHand(const bool AttachToHand)
{
	bIsAttachedToHand = AttachToHand;

	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(Owner);
	if (!UnleashedCharacter) return;

	if (UnleashedCharacter->GetMesh()->GetAnimInstance()->Implements<UAnimInstanceInterface>())
	{
		IAnimInstanceInterface::Execute_ChangeWeaponAttachedToHand(UnleashedCharacter->GetMesh()->GetAnimInstance(),
		                                                           bIsAttachedToHand);
	}
}
