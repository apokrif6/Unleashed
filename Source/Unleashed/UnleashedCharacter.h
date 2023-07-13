// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "UnleashedCharacter.generated.h"


struct FInputActionValue;
enum ECombatState : int;
class UInputAction;
class UCombatComponent;
class UCombatStateMachineComponent;
class UAttributesComponent;

UCLASS(config=Game)
class AUnleashedCharacter : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleCombatModeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HeavyAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RollAction;

	bool bInCombatMode = false;

	void PerformAttack();

	void PerformHeavyAttack();

	void PerformRoll();

	const float RollLastMovementVectorTolerance = 0.001f;

	UFUNCTION()
	void OnStateBegin(ECombatState CombatState);

	UFUNCTION()
	void OnStateEnd(ECombatState CombatState);

	UFUNCTION()
	void OnActorHit(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                class AController* InstigatedBy, AActor* DamageCauser);

	void OnDeadState();

public:
	AUnleashedCharacter();

	//TODO
	//should I use it, or replace it with "GetOwner()->GetComponentByClass()
	//hm...
	UCombatComponent* GetCombatComponent() const { return CombatComponent; }

	UCombatStateMachineComponent* GetCombatStateMachineComponent() const { return CombatStateMachineComponent; }

	UAttributesComponent* GetAttributesComponent() const { return AttributesComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void ContinueCombo() override;

	virtual FRotator GetRollRotation() override;

	virtual void ResetCombat() override;

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void ToggleCombatMode(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	void HeavyAttack(const FInputActionValue& Value);

	void Roll(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UCombatComponent* CombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UCombatStateMachineComponent* CombatStateMachineComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UAttributesComponent* AttributesComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dead")
	FName RagdollPhysicsBoneName = FName("pelvis");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dead")
	float RagdollPhysicsBlendWeight = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dead")
	float DeathDelay = 5.0f;
};
