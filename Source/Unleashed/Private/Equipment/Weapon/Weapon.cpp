// Unleashed


#include "Equipment/Weapon/Weapon.h"
#include "Interfaces/AnimInstanceInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Unleashed/UnleashedCharacter.h"

AWeapon::AWeapon()
{
	CombatCollisionComponent = CreateDefaultSubobject<ACombatCollisionComponent>("CombatCollisionComponent");
	CombatCollisionComponent->RegisterAllActorTickFunctions(true, true);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CombatCollisionComponent->OnActorHit.AddDynamic(this, &ThisClass::OnActorHit);
}

void AWeapon::Equip()
{
	SetIsEquipped(true);

	const AUnleashedCharacter* UnleashedCharacter = Cast<AUnleashedCharacter>(Owner);
	if (!UnleashedCharacter) return;

	if (UnleashedCharacter->GetCombatComponent()->GetInCombatMode())
	{
		AttachActorToOwner(HandAttachSocketName);
	}
	else
	{
		AttachActorToOwner(AttachSocketName);
	}

	UnleashedCharacter->GetCombatComponent()->SetMainWeapon(this);

	UnleashedCharacter->GetCombatComponent()->ResetCombat();

	if (UnleashedCharacter->GetMesh()->GetAnimInstance()->Implements<UAnimInstanceInterface>())
	{
		IAnimInstanceInterface::Execute_ChangeCombatStyle(UnleashedCharacter->GetMesh()->GetAnimInstance(),
		                                                  CombatStyle);
	}

	CombatCollisionComponent->SetCollisionMeshComponent(GetStaticMesh());

	CombatCollisionComponent->AddActorToIgnore(Owner);
}

void AWeapon::OnActorHit(FHitResult HitResult)
{
	UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), Damage, GetOwner()->GetActorForwardVector(), HitResult,
	                                   GetInstigatorController(), this, UDamageType::StaticClass());

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, HitResult.GetActor()->GetActorLocation());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, HitResult.GetActor()->GetActorLocation());

	ACharacter* Character = Cast<ACharacter>(HitResult.GetActor());

	if (!Character) return;

	Character->PlayAnimMontage(HitReactionAnimMontage);
}
