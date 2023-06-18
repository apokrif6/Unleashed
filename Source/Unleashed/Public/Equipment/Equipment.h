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

	void Equip();

	void Unequip();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	FName AttachSocketName = NAME_None;

	UPrimitiveComponent* GetStaticMesh() const;

	virtual void BeginPlay() override;

	void AttachActorToOwner(FName SocketName);

	bool IsEquipped() const { return bIsEquipped; }

private:
	bool bIsEquipped = false;
};
