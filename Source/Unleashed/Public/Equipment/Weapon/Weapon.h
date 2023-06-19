// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Equipment/Equipment.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class UNLEASHED_API AWeapon : public AEquipment
{
	GENERATED_BODY()

public:
	virtual void Equip() override;
};
