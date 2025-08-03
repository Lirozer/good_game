// Fill out your copyright notice in the Description page of Project Settings.

#include "ResetAttackNotify.h"

#include <Kismet/GameplayStatics.h>
#include "Warrior.h"

void UResetAttackNotify::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComponent, Animation, EventReference);

    AActor* pOwner = MeshComponent->GetOwner();

    if (nullptr != MeshComponent && nullptr != pOwner)
    {
        AWarrior* PWarrior = Cast<AWarrior>(pOwner);

        if (nullptr != PWarrior)
        {
            PWarrior->ResetAttack();
        }
    }
}
