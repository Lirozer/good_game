// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthWidget.h"
#include "Enemy.h"

float UEnemyHealthWidget::GetHealth()
{
    float OwnerHealth = Owner->GetHealth();

    return OwnerHealth / 100.0f;
}

void UEnemyHealthWidget::SetOwner(AEnemy *pOwner)
{
    this->Owner = pOwner;
}
