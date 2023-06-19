// Unleashed


#include "Pickups/WeaponPickup.h"
#include "Unleashed/UnleashedCharacter.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeaponPickup::Interact(AActor* InteractionInstigator)
{
	UWorld* World = GetWorld();
	if (!World) return;

	AWeapon* Weapon = World->SpawnActor<AWeapon>(WeaponToPickup);
	if (!Weapon) return;

	Weapon->SetOwner(InteractionInstigator);
	Weapon->Equip();

	Destroy();
}
