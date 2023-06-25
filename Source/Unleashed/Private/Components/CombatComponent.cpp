// Unleashed


#include "Components/CombatComponent.h"

#include "GameFramework/PawnMovementComponent.h"
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

	const ACharacter* CombatComponentOwner = Cast<ACharacter>(GetOwner());
	if (!CombatComponentOwner) return;

	if (CombatComponentOwner->GetMesh()->GetAnimInstance()->Implements<UAnimInstanceInterface>())
	{
		IAnimInstanceInterface::Execute_ChangeInCombatMode(CombatComponentOwner->GetMesh()->GetAnimInstance(),
		                                                   bInCombatMode);
	}
}

void UCombatComponent::AttachWeapon(const bool AttachToHand)
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

void UCombatComponent::ResetCombat()
{
	AttackCount = 0;

	bIsAttackSaved = false;

	bIsAttacking = false;

	bIsRolling = false;
}

void UCombatComponent::SetIsAttacking(const bool IsAttacking)
{
	bIsAttacking = IsAttacking;
}

void UCombatComponent::SetIsAttackSaved(const bool IsAttackSaved)
{
	bIsAttackSaved = IsAttackSaved;
}

void UCombatComponent::SetIsRolling(const bool IsRolling)
{
	bIsRolling = IsRolling;
}

bool UCombatComponent::CanRoll() const
{
	if (bIsRolling) return false;

	return true;
}

void UCombatComponent::IncreaseAttackCount()
{
	if (AttackCount + 1 >= GetMainWeapon()->GetAttackMontages().Num())
	{
		ResetCombat();
	}
	else
	{
		AttackCount++;
	}
}
