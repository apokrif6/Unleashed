// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseAttribute.generated.h"

/**
 * 
 */
USTRUCT()
struct FBaseAttribute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float BaseValue;

	UPROPERTY(EditAnywhere)
	float MaxValue;

	FBaseAttribute()
	{
		BaseValue = 100.f;
		MaxValue = 100.f;
	}

	FBaseAttribute(const float NewBaseValue, const float NewMaxValue)
	{
		BaseValue = NewBaseValue;
		MaxValue = NewMaxValue;
	}
};
