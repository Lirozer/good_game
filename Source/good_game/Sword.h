// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"

#include "Interaction.h"

#include "Sword.generated.h"

UCLASS()
class GOOD_GAME_API ASword : public AActor, public IInteraction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASword();

	virtual void Interact_Implementation() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent *Capsule = nullptr;
};
