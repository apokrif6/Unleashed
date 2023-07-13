// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UAttributeWidget;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class UNLEASHED_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* CanvasPanel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	UAttributeWidget* HealthAttributeWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	UAttributeWidget* StaminaAttributeWidget = nullptr;
};
