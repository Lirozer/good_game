// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ASword::ASword() : Super()
{
    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    SetRootComponent(Capsule);
}

void ASword::Interact_Implementation()
{
    UObject* pWorld = GetWorld();

    USkeletalMeshComponent *pPlayerMesh = UGameplayStatics::GetPlayerCharacter(pWorld, 0)->GetMesh();
    FAttachmentTransformRules AttachRules{EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true};

    AttachToComponent(pPlayerMesh, AttachRules, TEXT("WeaponPlace"));

    if (nullptr != Capsule)
    {
        Capsule->SetCapsuleSize(0, 0);
        Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

