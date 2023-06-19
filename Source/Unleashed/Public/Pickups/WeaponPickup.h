// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Equipment/Weapon/Weapon.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "WeaponPickup.generated.h"

UCLASS()
class UNLEASHED_API AWeaponPickup : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	AWeaponPickup();

	virtual void Interact(AActor* InteractionInstigator) override;;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AWeapon> WeaponToPickup;
};
