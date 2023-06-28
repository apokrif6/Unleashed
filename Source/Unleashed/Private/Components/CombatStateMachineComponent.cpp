// Unleashed


#include "Components/CombatStateMachineComponent.h"

UCombatStateMachineComponent::UCombatStateMachineComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UCombatStateMachineComponent::SetState(const ECombatState CombatState)
{
    if (State == CombatState) return;

    OnStateEnd.Broadcast(State);

    State = CombatState;

    OnStateBegin.Broadcast(State);
}

void UCombatStateMachineComponent::ResetState()
{
    State = Idling;
}

bool UCombatStateMachineComponent::IsStateEqualsToAnyOf(const TArray<ECombatState>& CombatStates) const
{
    if (CombatStates.Contains(State)) return true;

    return false;
}
