// Unleashed


#include "Components/AttributesComponent.h"
#include "Unleashed/UnleashedCharacter.h"

UAttributesComponent::UAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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

void UAttributesComponent::SetBaseAttributeValue(const ECombatAttribute Attribute, const float BaseValue)
{
	Attributes.Find(Attribute)->BaseValue = BaseValue;
}

void UAttributesComponent::SetMaxAttributeValue(const ECombatAttribute Attribute, const float MaxValue)
{
	Attributes.Find(Attribute)->MaxValue = MaxValue;
}

void UAttributesComponent::TakeDamage(const float Damage)
{
	ModifyCurrentAttributeValue(Health, -Damage);

	if (GetCurrentAttributeValue(Health) > 0.0f) return;

	const AUnleashedCharacter* ComponentOwner = Cast<AUnleashedCharacter>(GetOwner());
	if (!ComponentOwner) return;

	ComponentOwner->GetCombatStateMachineComponent()->SetState(Dead);
}
