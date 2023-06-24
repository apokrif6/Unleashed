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

	TArray<UAnimMontage*> GetAttackMontages() const { return AttackMontages; }

	UAnimMontage* GetDodgeMontage() const { return DodgeMontage; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attachments")
	FName HandAttachSocketName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipWeaponAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* UnequipWeaponAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UAnimMontage* DodgeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TEnumAsByte<ECombatStyle> CombatStyle;
};
