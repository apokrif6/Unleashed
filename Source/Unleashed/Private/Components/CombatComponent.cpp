// Unleashed


#include "Components/CombatComponent.h"

#include "Interfaces/AnimInstanceInterface.h"
#include "Unleashed/UnleashedCharacter.h"

UCombatComponent::UCombatComponent()
{
}

void UCombatComponent::SetMainWeapon(AWeapon* Weapon)
{
	if (MainWeapon)
	{
		MainWeapon->Unequip();
		MainWeapon->Destroy();
	}

	MainWeapon = Weapon;
}

void UCombatComponent::SetInCombatMode(const bool InCombatMode)
{
	bInCombatMode = InCombatMode;

	ACharacter* CombatComponentOwner = Cast<ACharacter>(GetOwner());
	if (!CombatComponentOwner) return;

	if (CombatComponentOwner->GetMesh()->GetAnimInstance()->Implements<UAnimInstanceInterface>())
	{
		IAnimInstanceInterface::Execute_ChangeInCombatMode(CombatComponentOwner->GetMesh()->GetAnimInstance(),
		                                                   bInCombatMode);
	}
}

void UCombatComponent::AttachWeapon(bool AttachToHand)
{
	if (AttachToHand)
	{
		MainWeapon->AttachActorToOwner(GetMainWeapon()->GetHandAttachSocketName());
	}
	else
	{
		MainWeapon->AttachActorToOwner(GetMainWeapon()->GetEquipmentAttachedSocketName());
	}

	SetInCombatMode(!GetInCombatMode());
}
