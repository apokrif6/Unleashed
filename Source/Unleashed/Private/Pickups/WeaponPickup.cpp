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
	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(InteractionInstigator);
	if (!UnleashedCharacter) return;

	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponToPickup);
	if (!Weapon) return;

	Weapon->SetOwner(InteractionInstigator);
	Weapon->Equip();

	Destroy();
}
