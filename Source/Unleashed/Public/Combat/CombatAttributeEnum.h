// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CombatAttributeEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ECombatAttribute
{
	NoneAttribute UMETA(DisplayName = "NoneAttribute"),
	Health UMETA(DisplayName = "Health"),
	Stamina UMETA(DisplayName = "Stamina"),
	Armor UMETA(DisplayName = "Armor"),
};
