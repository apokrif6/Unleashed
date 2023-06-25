// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNLEASHED_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual void ContinueCombo()
	{
	}

	virtual FRotator GetRollRotation()
	{
		return {};
	}

	virtual void ResetCombat()
	{
	}
};
