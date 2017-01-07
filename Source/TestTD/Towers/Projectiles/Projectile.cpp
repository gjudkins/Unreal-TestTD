// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "Baddies/BaddieCharacter.h"
#include "PaperSpriteComponent.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	speed = 200.0f;
	collisionRadius = 10.0f;
	damage = 15.0f;
	maxLifeDuration = 15.0f;

	RootComponent = projectileDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("towerArrowComponent"));	
	
	//projectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("projectileSprite"));
	//projectileSprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RootComponent->GetAttachSocketName());

	//static ConstructorHelpers::FObjectFinder<UPaperSprite> pSprite(TEXT("PaperSprite'/Game/Sprites/Towers/Projectiles/Towers_towers_251.Towers_towers_251'"));
	//projectileSprite->SetSprite(pSprite.Object);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	dieTime = GetWorld()->GetTimeSeconds() + maxLifeDuration;
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GetWorld()->GetTimeSeconds() > dieTime)
	{
		Destroy();
	}

	FVector Loc = GetActorLocation();
	FVector DesiredLocation = Loc + ((DeltaTime * speed) * GetTransform().GetUnitAxis(EAxis::X));

	FHitResult OutHit;
	if (UWorld* World = GetWorld()) {
		FCollisionShape CollisionShape;
		CollisionShape.SetCapsule(collisionRadius, 200.0f);
		if (World->SweepSingleByProfile(OutHit, Loc, DesiredLocation, FQuat::Identity, movementCollisionProfile, CollisionShape))
		{
			SetActorLocation(OutHit.Location);
			// use an interface for damagable or something rather than a straight class-check
			if (ABaddieCharacter* baddie = Cast<ABaddieCharacter>(OutHit.Actor.Get()))
			{
				baddie->Destroy();
				//baddie->ReceiveDamage(damage);
			}
			//Explode();
		}
		else
		{
			SetActorLocation(DesiredLocation);
		}
	}
}

