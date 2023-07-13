// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnleashedPlayerController.generated.h"

class UHUDWidget;
/**
 * 
 */
UCLASS()
class UNLEASHED_API AUnleashedPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHUDWidget> HUDWidgetClass = nullptr;
};
