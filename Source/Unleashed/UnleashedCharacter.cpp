// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnleashedCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interfaces/InteractInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


//////////////////////////////////////////////////////////////////////////
// AUnleashedCharacter

AUnleashedCharacter::AUnleashedCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	CombatStateMachineComponent = CreateDefaultSubobject<UCombatStateMachineComponent>(TEXT("CombatStateMachineComponent"));
}

void AUnleashedCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnActorHit);

	CombatStateMachineComponent->OnStateBegin.AddDynamic(this, &ThisClass::OnStateBegin);
	CombatStateMachineComponent->OnStateEnd.AddDynamic(this, &ThisClass::OnStateEnd);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUnleashedCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

		EnhancedInputComponent->BindAction(ToggleCombatModeAction, ETriggerEvent::Completed, this,
		                                   &ThisClass::ToggleCombatMode);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ThisClass::Interact);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &ThisClass::Attack);

		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Completed, this, &ThisClass::Roll);
	}
}

void AUnleashedCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AUnleashedCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AUnleashedCharacter::ToggleCombatMode(const FInputActionValue& Value)
{
	if (!CombatComponent->GetMainWeapon()) return;

	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying()) return;

	if (CombatStateMachineComponent->IsStateEqualsToAnyOf(TArray{Attacking, Rolling, General, Dead, Disabled})) return;

	CombatStateMachineComponent->SetState(General);

	if (CombatComponent->GetInCombatMode())
	{
		PlayAnimMontage(CombatComponent->GetMainWeapon()->GetEquipWeaponAnimMontage());
	}
	else
	{
		PlayAnimMontage(CombatComponent->GetMainWeapon()->GetUnequipWeaponAnimMontage());
	}
}

void AUnleashedCharacter::Interact(const FInputActionValue& Value)
{
	const UWorld* World = GetWorld();
	if (!World) return;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Reserve(1);
	ObjectTypes.Emplace(ECC_EngineTraceChannel1);

	const TArray<AActor*> IgnoredActors;
	FHitResult HitResult;

	const bool bHitResult = UKismetSystemLibrary::SphereTraceSingleForObjects(
		World, GetActorLocation(), GetActorLocation(),
		100.f, ObjectTypes, false, IgnoredActors,
		EDrawDebugTrace::None, HitResult, true);

	if (!bHitResult) return;

	if (IInteractInterface* InteractInterface = Cast<IInteractInterface>(HitResult.GetActor()))
	{
		InteractInterface->Interact(this);
	}
}

void AUnleashedCharacter::Attack(const FInputActionValue& Value)
{
	if (!CombatComponent->GetMainWeapon()) return;

	if (CombatStateMachineComponent->IsStateEqualsToAnyOf(TArray{Rolling, General, Disabled, Dead})) return;
	
	if (CombatStateMachineComponent->GetState() == Attacking)
	{
		CombatComponent->SetIsAttackSaved(true);
	}
	else
	{
		PerformAttack(CombatComponent->GetAttackCount());
	}
}

void AUnleashedCharacter::Roll(const FInputActionValue& Value)
{
	if (!CombatComponent->GetMainWeapon()) return;

	if (CombatStateMachineComponent->IsStateEqualsToAnyOf(TArray{Attacking, Rolling, General, Disabled, Dead})) return;

	PerformRoll();
}

void AUnleashedCharacter::PerformAttack(const int32 AttackIndex, const bool UseRandomIndex)
{
	TArray<UAnimMontage*> AttackMontages = CombatComponent->GetMainWeapon()->GetAttackMontages();
	if (AttackIndex >= AttackMontages.Num())
	{
		//TODO
		//log
		return;
	}

	UAnimMontage* AttackMontage = UseRandomIndex
		                              ? AttackMontages[FMath::RandRange(0, AttackMontages.Num() - 1)]
		                              : AttackMontage = AttackMontages[AttackIndex];
	if (!AttackMontage) return;

	CombatStateMachineComponent->SetState(Attacking);

	PlayAnimMontage(AttackMontage);

	CombatComponent->IncreaseAttackCount();
}

void AUnleashedCharacter::PerformRoll()
{
	UAnimMontage* DodgeAnimMontage = CombatComponent->GetMainWeapon()->GetDodgeMontage();

	CombatStateMachineComponent->SetState(Rolling);

	PlayAnimMontage(DodgeAnimMontage);
}

void AUnleashedCharacter::OnStateBegin(ECombatState CombatState)
{
}

void AUnleashedCharacter::OnStateEnd(ECombatState CombatState)
{
}

void AUnleashedCharacter::OnActorHit(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	CombatStateMachineComponent->SetState(Disabled);
}

void AUnleashedCharacter::ContinueCombo()
{
	if (CombatComponent->IsAttackSaved())
	{
		CombatComponent->SetIsAttackSaved(false);

		CombatStateMachineComponent->SetState(Idling);

		PerformAttack(CombatComponent->GetAttackCount());
	}
}

FRotator AUnleashedCharacter::GetRollRotation()
{
	const FVector LastInputVector = GetMovementComponent()->GetLastInputVector();

	if (!LastInputVector.Equals(FVector::ZeroVector, RollLastMovementVectorTolerance))
	{
		return UKismetMathLibrary::MakeRotFromX(LastInputVector);
	}

	return GetActorRotation();
}

void AUnleashedCharacter::ResetCombat()
{
	CombatComponent->ResetCombat();

	CombatStateMachineComponent->ResetState();
}
