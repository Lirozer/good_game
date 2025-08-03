// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

#include "Enemy.generated.h"

UCLASS()
class GOOD_GAME_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;

	float GetHealth();

	void Attack();

private:
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent *HealthBar = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent *SphereCollision = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage *HitReactAnimation1 = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage *HitReactAnimation2 = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage *AttackAnimation1 = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage *AttackAnimation2 = nullptr;

	float Health = 100;

	UFUNCTION()
	void ShowHealthBar();

	UFUNCTION()
	void HideHealthBar();
};
