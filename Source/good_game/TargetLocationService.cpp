// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetLocationService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

#define NAVIGABLE_RADIUS 500

UTargetLocationService::UTargetLocationService()
{
    NodeName = "Get Target Location";

    bNotifyBecomeRelevant = true;
}

void UTargetLocationService::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComponent, uint8 *NodeMemory)
{
    UObject *SelfActorObject = OwnerComponent.GetBlackboardComponent()->GetValueAsObject(SelfActorKey.SelectedKeyName);
    AActor *SelfActor = Cast<AActor>(SelfActorObject);

    UNavigationSystemV1 *NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(SelfActor);
    FVector TargetLocation;

    FVector OriginLocation = SelfActor->GetActorLocation();
    NavigationSystem->K2_GetRandomPointInNavigableRadius(SelfActor, OriginLocation, TargetLocation, NAVIGABLE_RADIUS);

    OwnerComponent.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, TargetLocation);
}