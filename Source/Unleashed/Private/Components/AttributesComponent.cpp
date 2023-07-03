// Unleashed


#include "Components/AttributesComponent.h"


UAttributesComponent::UAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UAttributesComponent::GetCurrentAttributeValue(const ECombatAttribute Attribute)
{
	const float* FoundAttribute = CurrentAttributes.Find(Attribute);
	if (!FoundAttribute) return 0.0f;

	return *FoundAttribute;
}

void UAttributesComponent::ModifyCurrentAttributeValue(const ECombatAttribute Attribute, const float ModifierValue)
{
	if (ModifierValue == 0.0f) return;

	const float ClampedValue = FMath::Clamp(GetCurrentAttributeValue(Attribute) + ModifierValue, 0.0f,
	                                        Attributes.Find(Attribute)->MaxValue);

	SetCurrentAttributeValue(Attribute, ClampedValue);
}

void UAttributesComponent::SetCurrentAttributeValue(const ECombatAttribute Attribute, const float Value)
{
	CurrentAttributes.Add(Attribute, Value);
}

void UAttributesComponent::InitializeAttributes()
{
	TArray<TEnumAsByte<ECombatAttribute>> OutKeys;
	Attributes.GetKeys(OutKeys);

	for (TEnumAsByte<ECombatAttribute> OutKey : OutKeys)
	{
		SetCurrentAttributeValue(OutKey, Attributes.Find(OutKey)->BaseValue);
	}
}
