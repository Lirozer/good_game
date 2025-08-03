// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"

#include "TargetLocationService.generated.h"

/**
 * 
 */
UCLASS()
class GOOD_GAME_API UTargetLocationService : public UBTService
{
	GENERATED_BODY()

public:
	UTargetLocationService();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent &OwnerComponent, uint8 *NodeMemory) override;
private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetLocationKey;
};
