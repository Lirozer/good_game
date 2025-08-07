// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#define MAX_WALK_SPEED            300
#define MAX_SPRINT_SPEED          600
#define MAX_BACK_WALK_SPEED       150

APlayerCharacter::APlayerCharacter() : Super()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
    Camera->SetupAttachment(SpringArm);

    SpringArm->bUsePawnControlRotation = true;
    Camera->bUsePawnControlRotation = false;

    GetCharacterMovement()->MaxWalkSpeed = MAX_WALK_SPEED;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInput)
{
    Super::SetupPlayerInputComponent(PlayerInput);

    PlayerInput->BindAxis("MoveForwardBack", this, &APlayerCharacter::MoveForwardBack);
    PlayerInput->BindAxis("MoveRightLeft", this, &APlayerCharacter::MoveRightLeft);

    PlayerInput->BindAxis("LookUpDown", this, &APlayerCharacter::LookUpDown);
    PlayerInput->BindAxis("LookLeftRight", this, &APlayerCharacter::LookLeftRight);

    PlayerInput->BindAction("Sprint", EInputEvent::IE_Pressed, this, &APlayerCharacter::StartSprinting);
    PlayerInput->BindAction("Sprint", EInputEvent::IE_Released, this, &APlayerCharacter::StopSprinting);

    PlayerInput->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);

    PlayerInput->BindAction("Action", EInputEvent::IE_Pressed, this, &APlayerCharacter::Action);
}

void APlayerCharacter::MoveForwardBack(float Value)
{
    if (0 == Value)
    {
        return;
    }

    GetCharacterMovement()->MaxWalkSpeed = MAX_WALK_SPEED;

    if (true == bIsSprinting)
    {
        GetCharacterMovement()->MaxWalkSpeed = MAX_SPRINT_SPEED;
    }

    bIsWalkingBackward = false;

    if (-1 == Value)
    {
        bIsWalkingBackward = true;
        GetCharacterMovement()->MaxWalkSpeed = MAX_BACK_WALK_SPEED;
    }

    FVector Direction = GetActorForwardVector();
    AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRightLeft(float Value)
{
    if (0 == Value)
    {
        return;
    }

    GetCharacterMovement()->MaxWalkSpeed = MAX_WALK_SPEED;

    bIsSprinting = false;

    if (true == bIsWalkingBackward)
    {
        GetCharacterMovement()->MaxWalkSpeed = MAX_BACK_WALK_SPEED;
        bIsWalkingBackward = false;
    }

    FVector Direction = GetActorRightVector();
    AddMovementInput(Direction, Value);
}

void APlayerCharacter::LookUpDown(float Value)
{
    AddControllerPitchInput(Value);
}

void APlayerCharacter::LookLeftRight(float Value)
{
    AddControllerYawInput(Value);
}

void APlayerCharacter::StartSprinting()
{
    bIsSprinting = true;
}

void APlayerCharacter::StopSprinting()
{
    bIsSprinting = false;
}

void APlayerCharacter::Action()
{
}
