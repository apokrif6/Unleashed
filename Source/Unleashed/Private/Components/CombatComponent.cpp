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
}

void UCombatComponent::SetIsAttackSaved(const bool IsAttackSaved)
{
	bIsAttackSaved = IsAttackSaved;
}

UAnimMontage* UCombatComponent::GetCurrentCombatStateAnimMontage(ECombatState CombatState) const
{
	switch (CombatState)
	{
	case Idling: break;
	case Attacking:
		return MainWeapon->GetAttackMontages()[AttackCount];
	case HeavyAttacking:
		return MainWeapon->GetHeavyAttackMontage();
	case Rolling:
		return MainWeapon->GetDodgeMontage();
	case General: break;
	case Disabled: break;
	case Dead: break;
	default: ;
	}
	return nullptr;
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
