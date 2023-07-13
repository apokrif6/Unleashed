// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatStyleEnum.h"
#include "Components/CombatCollisionComponent.h"
#include "Equipment/Equipment.h"
#include "Weapon.generated.h"

enum ECombatState : int;
/**
 * 
 */
UCLASS()
class UNLEASHED_API AWeapon : public AEquipment
{
	GENERATED_BODY()

public:
	AWeapon();

	virtual void Equip() override;

	virtual void BeginPlay() override;

	FName GetHandAttachSocketName() const { return HandAttachSocketName; }

	UAnimMontage* GetEquipWeaponAnimMontage() const { return EquipWeaponAnimMontage; }

	UAnimMontage* GetUnequipWeaponAnimMontage() const { return UnequipWeaponAnimMontage; }

	TArray<UAnimMontage*> GetAttackMontages() const { return AttackMontages; }

	UAnimMontage* GetHeavyAttackMontage() const { return HeavyAttackMontage; }

	UAnimMontage* GetDodgeMontage() const { return DodgeMontage; }

	ACombatCollisionComponent* GetCombatCollisionComponent() const { return CombatCollisionComponent; }

	float GetStaminaUsageForCombatState(ECombatState CombatState) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attachments")
	FName HandAttachSocketName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipWeaponAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* UnequipWeaponAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* HeavyAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DodgeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TEnumAsByte<ECombatStyle> CombatStyle;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float Damage = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TMap<TEnumAsByte<ECombatState>, float> StaminaUsage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UParticleSystem* HitParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* HitReactionAnimMontage;

private:
	UPROPERTY()
	ACombatCollisionComponent* CombatCollisionComponent;

	UFUNCTION()
	void OnActorHit(FHitResult HitResult);
};
