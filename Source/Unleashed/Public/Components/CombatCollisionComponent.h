// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatCollisionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorHit, FHitResult, HitResult);

UCLASS()
class UNLEASHED_API ACombatCollisionComponent : public AActor
{
	GENERATED_BODY()

public:
	ACombatCollisionComponent();

	virtual void Tick(float DeltaTime) override;

	void EnableCollision();

	void DisableCollision();

	void CollisionTrace();

	void ClearHitActors();

	void SetCollisionMeshComponent(UPrimitiveComponent* PrimitiveComponent);

	UPrimitiveComponent* GetCollisionMeshComponent() const { return CollisionMeshComponent; }

	TArray<AActor*> GetAlreadyHitActors() const { return AlreadyHitActors; }

	bool IsEnabled() const { return bIsEnabled; }

	FHitResult GetLastHitResult() const { return LastHitResult; }

	void AddActorToIgnore(AActor* Actor);

	void RemoveActorToIgnore(AActor* Actor);

	FOnActorHit OnActorHit;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UPrimitiveComponent* CollisionMeshComponent = nullptr;

	UPROPERTY()
	TArray<AActor*> AlreadyHitActors;

	bool bIsEnabled = false;

	FHitResult LastHitResult;

	FName StartSocketName = FName("WeaponStartSocket");

	FName EndSocketName = FName("WeaponEndSocket");

	float Radius = 25.f;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
};
