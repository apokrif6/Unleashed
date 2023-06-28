// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CombatStateEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ECombatState
{
	Idling UMETA(DisplayName = "Idling"),
	Attacking UMETA(DisplayName = "Attacking"),
	Rolling UMETA(DisplayName = "Rolling"),
	General UMETA(DisplayName = "General"),
	Disabled UMETA(DisplayName = "Disabled"),
	Dead UMETA(DisplayName = "Dead"),
};
