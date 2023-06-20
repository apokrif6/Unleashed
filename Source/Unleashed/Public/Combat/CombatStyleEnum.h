// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "CombatStyleEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ECombatStyle
{
	None UMETA(DisplayName = "None"),
	Sword UMETA(DisplayName = "Sword"),
	Greatsword UMETA(DisplayName = "Greatsword"),
};
