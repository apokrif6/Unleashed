// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

UCLASS()
class UNLEASHED_API AEquipment : public AActor
{
	GENERATED_BODY()

public:
	AEquipment();

	virtual void Equip();

	void Unequip();

	void AttachActorToOwner(FName SocketName);

	FName GetEquipmentAttachedSocketName() const { return AttachSocketName; }

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Attachments")
	FName AttachSocketName = NAME_None;

	UPrimitiveComponent* GetStaticMesh() const;

	virtual void BeginPlay() override;

	bool IsEquipped() const { return bIsEquipped; }

private:
	bool bIsEquipped = false;
};
