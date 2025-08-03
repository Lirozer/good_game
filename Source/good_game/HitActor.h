// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"

#include "HitActor.generated.h"

/**
 * 
 */
UCLASS()
class GOOD_GAME_API UHitActor : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyTick(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation) override;

private:
	bool bIsAttackFinished = true;
};
