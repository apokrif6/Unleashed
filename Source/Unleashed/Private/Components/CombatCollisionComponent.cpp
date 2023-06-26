// Unleashed


#include "Components/CombatCollisionComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ACombatCollisionComponent::ACombatCollisionComponent()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACombatCollisionComponent::EnableCollision()
{
	ClearHitActors();

	bIsEnabled = true;
}

void ACombatCollisionComponent::DisableCollision()
{
	bIsEnabled = false;
}

void ACombatCollisionComponent::CollisionTrace()
{
	const FVector StartLocation = CollisionMeshComponent->GetSocketLocation(StartSocketName);
	const FVector EndLocation = CollisionMeshComponent->GetSocketLocation(EndSocketName);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<FHitResult> HitResults;

	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), StartLocation, EndLocation, Radius, ObjectTypes, false,
	                                                 ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true);

	for (FHitResult HitResult : HitResults)
	{
		LastHitResult = HitResult;

		if (AlreadyHitActors.Contains(HitResult.GetActor())) continue;

		AlreadyHitActors.Add(HitResult.GetActor());

		OnActorHit.Broadcast(HitResult);
	}
}

void ACombatCollisionComponent::ClearHitActors()
{
	AlreadyHitActors.Empty();
}

void ACombatCollisionComponent::AddActorToIgnore(AActor* Actor)
{
	ActorsToIgnore.AddUnique(Actor);
}

void ACombatCollisionComponent::RemoveActorToIgnore(AActor* Actor)
{
	ActorsToIgnore.Remove(Actor);
}

void ACombatCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatCollisionComponent::Tick(float DeltaTime)
{
	if (!bIsEnabled) return;

	CollisionTrace();
}

void ACombatCollisionComponent::SetCollisionMeshComponent(UPrimitiveComponent* PrimitiveComponent)
{
	CollisionMeshComponent = PrimitiveComponent;
}
