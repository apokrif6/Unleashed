// Unleashed


#include "Components/AttributesComponent.h"
#include "Components/CombatStateMachineComponent.h"
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
	const float* FoundAttributeValue = CurrentAttributes.Find(Attribute);
	if (!FoundAttributeValue) return 0.0f;

	return *FoundAttributeValue;
}

float UAttributesComponent::GetBaseAttributeValue(const ECombatAttribute Attribute)
{
	return Attributes.Find(Attribute)->BaseValue;
}

float UAttributesComponent::GetMaxAttributeValue(const ECombatAttribute Attribute)
{
	return Attributes.Find(Attribute)->MaxValue;
}

void UAttributesComponent::ModifyCurrentAttributeValue(const ECombatAttribute Attribute, const float ModifierValue)
{
	if (ModifierValue == 0.0f) return;

	const float ClampedValue = FMath::Clamp(GetCurrentAttributeValue(Attribute) + ModifierValue, 0.0f,
	                                        GetMaxAttributeValue(Attribute));

	SetCurrentAttributeValue(Attribute, ClampedValue);
}

void UAttributesComponent::SetCurrentAttributeValue(const ECombatAttribute Attribute, const float Value)
{
	CurrentAttributes.Add(Attribute, Value);

	OnCurrentAttributeValueChange.Broadcast(Attribute, Value);
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

void UAttributesComponent::RegenerateCurrentAttributeValue(const ECombatAttribute Attribute)
{
	switch (Attribute)
	{
	case NoneAttribute: break;
	case Health: break;
	case Stamina:
		GetWorld()->GetTimerManager().SetTimer(RegenerateAttributeValueTimer, this, &ThisClass::RegenerateStamina,
		                                       StaminaRegenerateRate, true);
		break;
	default: ;
	}
}

void UAttributesComponent::RegenerateStamina()
{
	if (const float AttributeValue = GetCurrentAttributeValue(Stamina); AttributeValue >= GetMaxAttributeValue(Stamina))
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenerateAttributeValueTimer);
		return;
	}

	ModifyCurrentAttributeValue(Stamina, StaminaToRegenerate);
}
