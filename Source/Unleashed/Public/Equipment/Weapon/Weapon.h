// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatStyleEnum.h"
#include "Equipment/Equipment.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class UNLEASHED_API AWeapon : public AEquipment
{
	GENERATED_BODY()

public:
	virtual void Equip() override;

	FName GetHandAttachSocketName() const { return HandAttachSocketName; }

	UAnimMontage* GetEquipWeaponAnimMontage() const { return EquipWeaponAnimMontage; }

	UAnimMontage* GetUnequipWeaponAnimMontage() const { return UnequipWeaponAnimMontage; }

	bool IsAttachedToHand() const { return bIsAttachedToHand; }

	void SetAttachedToHand(bool AttachToHand);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attachments")
	FName HandAttachSocketName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipWeaponAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* UnequipWeaponAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TEnumAsByte<ECombatStyle> CombatStyle;

private:
	bool bIsAttachedToHand = false;
};
