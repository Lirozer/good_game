// Fill out your copyright notice in the Description page of Project Settings.


#include "Warrior.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"

#include "Interaction.h"

#define LINE_TRACE_SIZE           200

#define ANIMATION_ATTACK_NUMBER   3
#define ATTACK_DELAY              1

// Sets default values
AWarrior::AWarrior() : Super()
{
    ExtraCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ExtraCamera"));
    USkeletalMeshComponent *pMesh = GetMesh();
    ExtraCamera->SetupAttachment(pMesh, "Head");

    GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AWarrior::SetupPlayerInputComponent(UInputComponent *PlayerInput)
{
    Super::SetupPlayerInputComponent(PlayerInput);

    PlayerInput->BindAction("ChangeCamera", EInputEvent::IE_Pressed, this, &AWarrior::ChangeCamera);

    PlayerInput->BindAction("Crouch", EInputEvent::IE_Pressed, this, &AWarrior::Crouch);
    PlayerInput->BindAction("Crouch", EInputEvent::IE_Released, this, &AWarrior::UnCrouch);

    PlayerInput->BindAction("EquipWeapon", EInputEvent::IE_Pressed, this, &AWarrior::EquipWeapon);

    PlayerInput->BindAction("Attack", EInputEvent::IE_Pressed, this, &AWarrior::Attack);

    PlayerInput->BindAction("Block", EInputEvent::IE_Pressed, this, &AWarrior::Block);
    PlayerInput->BindAction("Block", EInputEvent::IE_Released, this, &AWarrior::StopBlock);
}

void AWarrior::PossessedBy(AController *NewController)
{
    GetMesh()->SetVisibility(true);
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AWarrior::UnPossessed()
{
    GetMesh()->SetVisibility(false);
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWarrior::ResetAttack()
{
    bIsAttackDone = false;
}

void AWarrior::Crouch()
{
    Super::Crouch();
}

void AWarrior::UnCrouch()
{
    Super::UnCrouch();
}

void AWarrior::ChangeCamera()
{
    if (true == bIsThirdPersonView)
    {
        Camera->Deactivate();
        ExtraCamera->Activate();
        bUseControllerRotationYaw = true;
        bIsThirdPersonView = false;
    }
    else
    {
        ExtraCamera->Deactivate();
        Camera->Activate();
        bUseControllerRotationYaw = false;
        bIsThirdPersonView = true;
    }
}

void AWarrior::Action()
{
    bool bIsBound = OnHorseRideDelegate.IsBound();

    if (true == bIsBound)
    {
        OnHorseRideDelegate.Execute();
    }

    FVector ForwardVector = ExtraCamera->GetForwardVector();

    FVector StartLine = ExtraCamera->GetComponentLocation();
    FVector EndLine = (ForwardVector * LINE_TRACE_SIZE) + StartLine;

    FHitResult HitResult;

    GetWorld()->LineTraceSingleByChannel(HitResult, StartLine, EndLine, ECollisionChannel::ECC_Visibility);
    DrawDebugLine(GetWorld(), StartLine, EndLine, FColor::Red, false, 1.0f);

    if (true == HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Red, false, 1.0f);

        Weapon = HitResult.GetActor();

        FString HitResultName = UKismetSystemLibrary::GetDisplayName(Weapon);
        GEngine->AddOnScreenDebugMessage(-1, 1.0F, FColor::Blue, HitResultName);

        UClass *InteractionInterface = UInteraction::StaticClass();
        bool bIsInteract = UKismetSystemLibrary::DoesImplementInterface(Weapon, InteractionInterface);

        if (true == bIsInteract)
        {
            PlayAnimMontage(PickItemAnimation);
            IInteraction::Execute_Interact(Weapon);

            bHasWeapon = true;
        }
    }
}

void AWarrior::EquipWeapon()
{
    if (false == bHasWeapon)
    {
        return;
    }

    USkeletalMeshComponent* pMesh = GetMesh();
    FAttachmentTransformRules AttachmentRules{ EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false };

    if (false == bIsWeaponEquipped)
    {
        PlayAnimMontage(EquipWeaponAnimation, -1.0f);

        Weapon->AttachToComponent(pMesh, AttachmentRules, TEXT("WeaponEquipPlace"));
        bIsWeaponEquipped = true;
    }
    else
    {
        PlayAnimMontage(EquipWeaponAnimation, -1.0f);

        Weapon->AttachToComponent(pMesh, AttachmentRules, TEXT("WeaponPlace"));
        bIsWeaponEquipped = false;
    }
}

void AWarrior::Attack()
{
    if (false == bIsWeaponEquipped)
    {
        EquipWeapon();
        return;
    }

    if (true == bIsAttackDone)
    {
        return;
    }

    bIsAttackDone = true;

    switch (AnimationAttackCounter)
    {
        case 0:
        {
            PlayAnimMontage(FirstAttackAnimation);
        }
        break;

        case 1:
        {
            PlayAnimMontage(SecondAttackAnimation);
        }
        break;

        case 2:
        {
            PlayAnimMontage(ThirdAttackAnimation);
        }
        break;

        default:
        {
            
        }
        break;
    }

    AnimationAttackCounter++;
    AnimationAttackCounter %= ANIMATION_ATTACK_NUMBER;

    StartRetriggerableDelay();
}

void AWarrior::StartRetriggerableDelay()
{
    FLatentActionInfo LatentAction;
    LatentAction.CallbackTarget = this;
    LatentAction.ExecutionFunction = TEXT("ResetAnimationAttackCounter");
    LatentAction.Linkage = 0;
    LatentAction.UUID = 0;

    UKismetSystemLibrary::RetriggerableDelay(this, ATTACK_DELAY, LatentAction);
}

void AWarrior::ResetAnimationAttackCounter()
{
    AnimationAttackCounter = 0;
}

void AWarrior::Block()
{
    if (false == bIsWeaponEquipped)
    {
        return;
    }

    if (true == bIsAttackDone)
    {
        return;
    }

    PlayAnimMontage(BlockAnimation, 1.0f, TEXT("Loop"));
}

void AWarrior::StopBlock()
{
    if (false == bIsWeaponEquipped)
    {
        return;
    }

    StopAnimMontage(BlockAnimation);
}

