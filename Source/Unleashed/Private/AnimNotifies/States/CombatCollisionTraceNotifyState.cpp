// Unleashed


#include "AnimNotifies/States/CombatCollisionTraceNotifyState.h"
#include "Components/CombatComponent.h"
#include "Unleashed/UnleashedCharacter.h"

void UCombatCollisionTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                   float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	const AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(MeshComp->GetOwner());
	if (!UnleashedCharacter) return;

	UnleashedCharacter->GetCombatComponent()->GetMainWeapon()->GetCombatCollisionComponent()->EnableCollision();
}

void UCombatCollisionTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                 const FAnimNotifyEventReference& EventReference)
{
	const AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(MeshComp->GetOwner());
	if (!UnleashedCharacter) return;

	UnleashedCharacter->GetCombatComponent()->GetMainWeapon()->GetCombatCollisionComponent()->DisableCollision();
}
