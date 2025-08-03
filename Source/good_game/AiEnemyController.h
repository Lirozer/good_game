// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "AiEnemyController.generated.h"

class UBehaviorTree;
class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class GOOD_GAME_API AAiEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AAiEnemyController();

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree *BehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UAIPerceptionComponent *Perception = nullptr;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*> &UpdatedActors);
	
};
