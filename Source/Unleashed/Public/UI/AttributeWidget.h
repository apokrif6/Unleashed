// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Combat/CombatAttributeEnum.h"
#include "AttributeWidget.generated.h"

enum ECombatAttribute : int;
class UAttributesComponent;
class UProgressBar;
/**
 * 
 */
UCLASS()
class UNLEASHED_API UAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(Meta = (BindWidget))
	UProgressBar* AttributeBar = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "Attributes")
	TEnumAsByte<ECombatAttribute> Attribute = NoneAttribute;

private:
	UFUNCTION()
	void UpdateAttributeBar(ECombatAttribute CombatAttribute, float CurrentValue);

	UPROPERTY()
	UAttributesComponent* AttributesComponent = nullptr;
};
