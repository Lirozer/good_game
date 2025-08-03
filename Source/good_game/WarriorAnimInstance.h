// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementAnimations.h"

#include "WarriorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GOOD_GAME_API UWarriorAnimInstance : public UMovementAnimations
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	float Direction = 0;

	UPROPERTY(BlueprintReadOnly)
	bool bIsJumping = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCrouching = false;
};
