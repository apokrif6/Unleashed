// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatStyleEnum.h"
#include "UObject/Interface.h"
#include "AnimInstanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNLEASHED_API IAnimInstanceInterface
{
	GENERATED_BODY()

	// This interface is used in AnimationBlueprint, which is inherited from AnimInstance. So use IAnimInstanceInterface::Execute_ChangeCombatStyle()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void ChangeCombatStyle(ECombatStyle CombatStyle);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void ChangeInCombatMode(bool InCombatMode);
};
