// Fill out your copyright notice in the Description page of Project Settings.


#include "Horse.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Warrior.h"

#define MAX_WALK_SPEED       300
#define MAX_SPRINT_SPEED     600

AHorse::AHorse() : Super()
{
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxCollision->SetupAttachment(RootComponent);

    USkeletalMeshComponent *pMesh = GetMesh();

    AttachCharacter = CreateDefaultSubobject<USceneComponent>(TEXT("AttachCharacter"));
    AttachCharacter->SetupAttachment(pMesh, "Chest");

    AttachCharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    AttachCharacterMesh->SetupAttachment(AttachCharacter);
    AttachCharacterMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
    AttachCharacterMesh->SetVisibility(false);

    DeattachCharacter = CreateDefaultSubobject<USceneComponent>(TEXT("DeattachCharacter"));
    DeattachCharacter->SetupAttachment(pMesh, "Chest");
}

void AHorse::BeginPlay()
{
    Super::BeginPlay();

    FScriptDelegate OnBoxBeginOverlapDelegate;
    OnBoxBeginOverlapDelegate.BindUFunction(this, TEXT("OnBoxBeginOverlap"));
    BoxCollision->OnComponentBeginOverlap.Add(OnBoxBeginOverlapDelegate);

    FScriptDelegate OnBoxEndOverlapDelegate;
    OnBoxEndOverlapDelegate.BindUFunction(this, TEXT("OnBoxEndOverlap"));
    BoxCollision->OnComponentEndOverlap.Add(OnBoxEndOverlapDelegate);
}

void AHorse::OnBoxBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    AWarrior *Player = Cast<AWarrior>(OtherActor);

    if (nullptr != Player)
    {
        Player->OnHorseRideDelegate.BindUFunction(this, TEXT("Ride"));
    }
}

void AHorse::OnBoxEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    AWarrior *Player = Cast<AWarrior>(OtherActor);

    if (nullptr != Player)
    {
        Player->OnHorseRideDelegate.Unbind();
    }
}

void AHorse::Ride()
{
    Rider = UGameplayStatics::GetPlayerCharacter(this, 0);

    AController *PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    PlayerController->Possess(this);
    AttachCharacterMesh->SetVisibility(true);
}

void AHorse::Action()
{
    Super::Action();

    UnRide();
}

void AHorse::UnRide()
{
    FVector RiderLocation = DeattachCharacter->GetComponentLocation();
    FVector RiderScale = Rider->GetActorScale3D();

    FTransform3d Transform;
    Transform.SetLocation(RiderLocation);
    Transform.SetScale3D(RiderScale);

    Rider->SetActorTransform(Transform);

    AController *PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    PlayerController->Possess(Rider);

    AttachCharacterMesh->SetVisibility(false);
}
