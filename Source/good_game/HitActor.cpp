// Fill out your copyright notice in the Description page of Project Settings.

#include "HitActor.h"
#include "Kismet/GameplayStatics.h"

#define SPHERE_TRACE_RADIUS   5
#define DAMAGE                10
#define CYLINDER_SEGMENTS     12

void UHitActor::NotifyTick(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float FrameDeltaTime)
{
    Super::NotifyTick(MeshComponent, Animation, FrameDeltaTime);

    if (false == bIsAttackFinished)
    {
        return;
    }

    FVector AttackStart = MeshComponent->GetSocketLocation("AttackStart");
    FVector AttackEnd = MeshComponent->GetSocketLocation("AttackEnd");

    FHitResult HitResult;

    FCollisionShape SphereCollision = FCollisionShape::MakeSphere(SPHERE_TRACE_RADIUS);

    UWorld *pWorld = MeshComponent->GetWorld();

    pWorld->SweepSingleByChannel(HitResult, AttackStart, AttackEnd, FQuat::Identity, ECollisionChannel::ECC_Visibility, SphereCollision);
    DrawDebugCylinder(pWorld, AttackStart, AttackEnd, SPHERE_TRACE_RADIUS, 8, FColor::Red, false, 1.0f);

    if (true == HitResult.bBlockingHit)
    {
        AActor *pHitActor = HitResult.GetActor();
        UGameplayStatics::ApplyDamage(pHitActor, DAMAGE, nullptr, nullptr, nullptr);

        bIsAttackFinished = false;
    }
}

void UHitActor::NotifyEnd(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation)
{
    Super::NotifyEnd(MeshComponent, Animation);

    bIsAttackFinished = true;
}
