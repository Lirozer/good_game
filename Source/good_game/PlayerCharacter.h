// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GOOD_GAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInput) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent *SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent *Camera = nullptr;

	bool bIsSprinting = false;
	bool bIsWalkingBackward = false;

	virtual void MoveForwardBack(float Value);
	virtual void MoveRightLeft(float Value);

	void StartSprinting();
	void StopSprinting();

	virtual void Action();
};
