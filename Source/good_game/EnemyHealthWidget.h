// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "EnemyHealthWidget.generated.h"

class AEnemy;

/**
 * 
 */
UCLASS()
class GOOD_GAME_API UEnemyHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealth();

	void SetOwner(AEnemy *pOwner);
	
private:
	AEnemy *Owner = nullptr;
};
