// Fill out your copyright notice in the Description page of Project Settings.


#include "AiEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Warrior.h"

#define SIGHT_RADIUS           3000
#define LOSE_SIGHT_RADIUS      3500
#define VISION_ANGLE_DEGREES   90

AAiEnemyController::AAiEnemyController() : Super()
{
    Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

    UAISenseConfig_Sight *SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
    SightConfig->SightRadius = SIGHT_RADIUS;
    SightConfig->LoseSightRadius = LOSE_SIGHT_RADIUS;
    SightConfig->PeripheralVisionAngleDegrees = VISION_ANGLE_DEGREES;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    Perception->ConfigureSense(*SightConfig);

    FScriptDelegate OnPerceptionUpdatedDelegate;
    OnPerceptionUpdatedDelegate.BindUFunction(this, TEXT("OnPerceptionUpdated"));

    Perception->OnPerceptionUpdated.Add(OnPerceptionUpdatedDelegate);
}

void AAiEnemyController::BeginPlay()
{
    Super::BeginPlay();

    if (nullptr != BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
    }
}

void AAiEnemyController::OnPerceptionUpdated(const TArray<AActor*> &UpdatedActors)
{
    AWarrior *Player = nullptr;

    for (AActor *UpdatedActor : UpdatedActors)
    {
        Player = Cast<AWarrior>(UpdatedActor);

        if (nullptr != Player)
        {
            break;
        }
    }

    GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), Player);
}
