// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "MovementAnimations.generated.h"

/**
 * 
 */
UCLASS()
class GOOD_GAME_API UMovementAnimations : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	float Speed = 0;

protected:
	APawn *Owner = nullptr;
};
