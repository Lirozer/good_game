// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "EnemyAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class GOOD_GAME_API UEnemyAttackTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UEnemyAttackTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComponent, uint8 *NodeMemory) override;
};
