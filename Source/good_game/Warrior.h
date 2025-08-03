// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "Warrior.generated.h"

DECLARE_DELEGATE(FOnHorseRideDelegate)

UCLASS()
class GOOD_GAME_API AWarrior : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarrior();

	FOnHorseRideDelegate OnHorseRideDelegate;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInput) override;

	virtual void PossessedBy(AController *NewController) override;
	virtual void UnPossessed() override;

	void ResetAttack();

private:
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent *ExtraCamera = nullptr;

	bool bIsThirdPersonView = true;

	bool bHasWeapon = false;
	bool bIsWeaponEquipped = false;

	UPROPERTY(EditDefaultsOnly, Category = "Animation");
	UAnimMontage *PickItemAnimation = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animation\\Fight");
	UAnimMontage *EquipWeaponAnimation = nullptr;

	AActor *Weapon = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animation\\Fight\\Attack");
	UAnimMontage *FirstAttackAnimation = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animation\\Fight\\Attack");
	UAnimMontage *SecondAttackAnimation = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animation\\Fight\\Attack");
	UAnimMontage *ThirdAttackAnimation = nullptr;

	bool bIsAttackDone = false;
	int AnimationAttackCounter = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Animation\\Fight\\Block");
	UAnimMontage *BlockAnimation = nullptr;

	void Crouch();
	void UnCrouch();

	void ChangeCamera();

	virtual void Action() override;

	void EquipWeapon();

	void Attack();

	void StartRetriggerableDelay();
	void ResetAnimationAttackCounter();

	void Block();
	void StopBlock();
};
