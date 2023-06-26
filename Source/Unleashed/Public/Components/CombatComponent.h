// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment/Weapon/Weapon.h"
#include "CombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNLEASHED_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

	void SetMainWeapon(AWeapon* Weapon);

	AWeapon* GetMainWeapon() const { return MainWeapon; }

	void SetInCombatMode(const bool InCombatMode);

	bool GetInCombatMode() const { return bInCombatMode; }

	void AttachWeapon(bool AttachToHand);

	void ResetCombat();

	void IncreaseAttackCount();

	int32 GetAttackCount() const { return AttackCount; }

	void SetIsAttacking(bool IsAttacking);

	bool IsAttacking() const { return bIsAttacking; }

	void SetIsAttackSaved(bool IsAttackSaved);

	bool IsAttackSaved() const { return bIsAttackSaved; }

	void SetIsRolling(const bool IsRolling);

	bool CanRoll() const;

private:
	UPROPERTY()
	AWeapon* MainWeapon = nullptr;

	bool bInCombatMode = false;

	int32 AttackCount = 0;

	bool bIsAttacking = false;

	bool bIsAttackSaved = false;

	bool bIsRolling = false;
};
