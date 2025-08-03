// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementAnimations.h"

void UMovementAnimations::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Owner = TryGetPawnOwner();
}

void UMovementAnimations::NativeUpdateAnimation(float DeltaSeconds)
{
    if (nullptr != Owner)
    {
        FVector Velocity = Owner->GetVelocity();
        Speed = Velocity.Size();
    }
}
