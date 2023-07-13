// Unleashed


#include "PlayerController/UnleashedPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "UI/HUDWidget.h"

void AUnleashedPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//HUDWidgetClass

	UHUDWidget* HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}
