// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Combat/BaseAttribute.h"
#include "Combat/CombatAttributeEnum.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNLEASHED_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributesComponent();

	float GetCurrentAttributeValue(const ECombatAttribute Attribute);

	void ModifyCurrentAttributeValue(const ECombatAttribute Attribute, const float ModifierValue);

	void InitializeAttributes();

	void SetBaseAttributeValue(const ECombatAttribute Attribute, const float BaseValue);

	void SetMaxAttributeValue(const ECombatAttribute Attribute, const float MaxValue);

	void TakeDamage(const float Damage);

protected:
	UPROPERTY(EditAnywhere, Category="Attributes")
	TMap<TEnumAsByte<ECombatAttribute>, FBaseAttribute> Attributes;

private:
	void SetCurrentAttributeValue(const ECombatAttribute Attribute, const float Value);

	TMap<ECombatAttribute, float> CurrentAttributes;
};
