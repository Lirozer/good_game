// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyHealthWidget.h"

#define SPHERE_COLLISION_RADIUS 500

AEnemy::AEnemy() : Super()
{
    HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
    HealthBar->SetupAttachment(RootComponent);
    HealthBar->SetVisibility(false);

    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    SphereCollision->SetupAttachment(RootComponent);
    SphereCollision->InitSphereRadius(SPHERE_COLLISION_RADIUS);
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    HealthBar->SetWidgetSpace(EWidgetSpace::Screen);

    UUserWidget *UserWidget = HealthBar->GetUserWidgetObject();
    UEnemyHealthWidget *HealthBarWidget = Cast<UEnemyHealthWidget>(UserWidget);

    HealthBarWidget->SetOwner(this);

    FScriptDelegate ShowHealthBarDelegate;
    ShowHealthBarDelegate.BindUFunction(this, TEXT("ShowHealthBar"));
    SphereCollision->OnComponentBeginOverlap.Add(ShowHealthBarDelegate);

    FScriptDelegate HideHealthBarDelegate;
    HideHealthBarDelegate.BindUFunction(this, TEXT("HideHealthBar"));
    SphereCollision->OnComponentEndOverlap.Add(HideHealthBarDelegate);
}

float AEnemy::TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    Health -= Damage;

    float RandomValue = FMath::FRand();
    int AnimationIndex = std::round(RandomValue);

    if (0 == AnimationIndex)
    {
        PlayAnimMontage(HitReactAnimation1);
    }
    else
    {
        PlayAnimMontage(HitReactAnimation2);
    }

    if (Health <= 0)
    {
        Destroy();
    }

    return Damage;
}

void AEnemy::ShowHealthBar()
{
    HealthBar->SetVisibility(true);
}

void AEnemy::HideHealthBar()
{
    HealthBar->SetVisibility(false);
}

float AEnemy::GetHealth()
{
    return Health;
}

void AEnemy::Attack()
{
    float RandomValue = FMath::FRand();
    int AnimationIndex = std::round(RandomValue);

    if (0 == AnimationIndex)
    {
        PlayAnimMontage(AttackAnimation1);
    }
    else
    {
        PlayAnimMontage(AttackAnimation2);
    }
}
