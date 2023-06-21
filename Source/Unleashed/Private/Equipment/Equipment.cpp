// Unleashed


#include "Equipment/Equipment.h"
#include "Unleashed/UnleashedCharacter.h"

AEquipment::AEquipment()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
}

void AEquipment::Equip()
{
	SetIsEquipped(true);

	AttachActorToOwner(AttachSocketName);
}

void AEquipment::Unequip()
{
	if (IsEquipped())
		SetIsEquipped(false);
}

void AEquipment::BeginPlay()
{
	Super::BeginPlay();
}

void AEquipment::AttachActorToOwner(const FName SocketName)
{
	const AUnleashedCharacter* EquipmentOwner = Cast<AUnleashedCharacter>(GetOwner());

	if (!EquipmentOwner)
		return;

	GetStaticMesh()->AttachToComponent(EquipmentOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
	                                   SocketName);
}

void AEquipment::SetIsEquipped(bool IsEquipped)
{
	bIsEquipped = IsEquipped;
}

UPrimitiveComponent* AEquipment::GetStaticMesh() const
{
	if (!StaticMeshComponent)
		return SkeletalMeshComponent;

	return StaticMeshComponent;
}
