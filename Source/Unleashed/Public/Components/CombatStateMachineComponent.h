// Unleashed

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat/CombatStateEnum.h"
#include "CombatStateMachineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateBegin, ECombatState, CombatState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateEnd, ECombatState, CombatState);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNLEASHED_API UCombatStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatStateMachineComponent();

	void SetState(ECombatState CombatState);

	UFUNCTION(BlueprintCallable)
	ECombatState GetState() const { return State; }

	void ResetState();

	bool IsStateEqualsToAnyOf(const TArray<ECombatState>& CombatStates) const;

	FOnStateBegin OnStateBegin;

	FOnStateEnd OnStateEnd;

private:
	ECombatState State = Idling;
};
