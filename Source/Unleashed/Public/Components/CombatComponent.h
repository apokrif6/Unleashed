// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment/Weapon/Weapon.h"
#include "CombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNLEASHED_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCombatComponent();

	void SetMainWeapon(AWeapon* Weapon);

	AWeapon* GetMainWeapon() const { return MainWeapon; }

	void SetInCombatMode(const bool InCombatMode);

	bool GetInCombatMode() const { return bInCombatMode; }

	void AttachWeapon(bool AttachToHand);

private:
	UPROPERTY()
	AWeapon* MainWeapon = nullptr;

	bool bInCombatMode = false;
};
