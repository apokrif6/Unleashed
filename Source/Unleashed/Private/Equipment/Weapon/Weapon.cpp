// Unleashed


#include "Equipment/Weapon/Weapon.h"
#include "Unleashed/UnleashedCharacter.h"

void AWeapon::Equip()
{
	Super::Equip();

	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(Owner);
	if (!UnleashedCharacter) return;

	UnleashedCharacter->SetWeapon(this);
}
