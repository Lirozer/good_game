// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy.h"

UEnemyAttackTask::UEnemyAttackTask() : Super()
{
}

EBTNodeResult::Type UEnemyAttackTask::ExecuteTask(UBehaviorTreeComponent &OwnerComponent, uint8 *NodeMemory)
{
    UObject *EnemyObject = OwnerComponent.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor"));
    AEnemy *Enemy = Cast<AEnemy>(EnemyObject);

    Enemy->Attack();

    return EBTNodeResult::Succeeded;
}
