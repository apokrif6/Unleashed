// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Combat/BaseAttribute.h"
#include "Combat/CombatAttributeEnum.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentAttributeValueChange, ECombatAttribute, CurrentAttribute, float,
                                             CurrentValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNLEASHED_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributesComponent();

	float GetCurrentAttributeValue(const ECombatAttribute Attribute);

	float GetBaseAttributeValue(const ECombatAttribute Attribute);

	float GetMaxAttributeValue(const ECombatAttribute Attribute);

	void ModifyCurrentAttributeValue(const ECombatAttribute Attribute, const float ModifierValue);

	void InitializeAttributes();

	void SetBaseAttributeValue(const ECombatAttribute Attribute, const float BaseValue);

	void SetMaxAttributeValue(const ECombatAttribute Attribute, const float MaxValue);

	void TakeDamage(const float Damage);

	void RegenerateCurrentAttributeValue(const ECombatAttribute Attribute);

	FOnCurrentAttributeValueChange OnCurrentAttributeValueChange;

protected:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TMap<TEnumAsByte<ECombatAttribute>, FBaseAttribute> Attributes;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaToRegenerate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaRegenerateRate = 0.1f;

private:
	void SetCurrentAttributeValue(const ECombatAttribute Attribute, const float Value);

	TMap<ECombatAttribute, float> CurrentAttributes;

	FTimerHandle RegenerateAttributeValueTimer;

	UFUNCTION()
	void RegenerateStamina();
};
