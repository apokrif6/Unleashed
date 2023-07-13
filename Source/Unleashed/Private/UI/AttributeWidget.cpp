// Unleashed


#include "UI/AttributeWidget.h"
#include "Components/AttributesComponent.h"
#include "Components/ProgressBar.h"
#include "Unleashed/UnleashedCharacter.h"

void UAttributeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(GetOwningPlayerPawn());
	if (!UnleashedCharacter) return;

	AttributesComponent = UnleashedCharacter->GetAttributesComponent();

	ensureMsgf(Attribute != NoneAttribute, TEXT("Attribute for widget should be defined"));

	AttributesComponent->OnCurrentAttributeValueChange.AddDynamic(this, &ThisClass::UpdateAttributeBar);
}

void UAttributeWidget::UpdateAttributeBar(ECombatAttribute CombatAttribute, float CurrentValue)
{
	if (CombatAttribute != Attribute) return;

	AttributeBar->SetPercent(CurrentValue / AttributesComponent->GetMaxAttributeValue(CombatAttribute));
}
