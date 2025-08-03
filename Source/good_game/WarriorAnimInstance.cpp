// Fill out your copyright notice in the Description page of Project Settings.

#include "WarriorAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (nullptr != Owner)
	{
		FVector Velocity = Owner->GetVelocity();
		FRotator Rotation = Owner->GetActorRotation();

		Direction = CalculateDirection(Velocity, Rotation);

		bIsJumping = Owner->GetMovementComponent()->IsFalling();
		bIsCrouching = Owner->GetMovementComponent()->IsCrouching();
	}
}
