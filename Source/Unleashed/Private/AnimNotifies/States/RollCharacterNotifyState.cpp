// Unleashed


#include "AnimNotifies/States/RollCharacterNotifyState.h"
#include "Unleashed/UnleashedCharacter.h"

void URollCharacterNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(MeshComp->GetOwner());
	if (!UnleashedCharacter) return;

	const FRotator RollRotation = FMath::RInterpConstantTo(UnleashedCharacter->GetActorRotation(),
	                                                 UnleashedCharacter->GetRollRotation(),
	                                                 FrameDeltaTime, InterpSpeed);

	UnleashedCharacter->SetActorRotation(RollRotation);
}
