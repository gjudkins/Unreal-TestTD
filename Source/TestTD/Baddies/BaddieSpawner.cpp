// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "TestTDStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaddieSpawner.h"


// Sets default values
ABaddieSpawner::ABaddieSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.TickInterval = 2.0f;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	FVector boxExtent = SpawnVolume->GetUnscaledBoxExtent();
	boxExtent.Z = 100.0f;
	SpawnVolume->SetBoxExtent(boxExtent, false);
	if (RootComponent)
	{
		SpawnVolume->SetupAttachment(RootComponent);
	}
	else
	{
		RootComponent = SpawnVolume;
	}
}

// Called when the game starts or when spawned
void ABaddieSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	TestTDStatics::putInCombatZPlane(this);
}

// Called every frame
void ABaddieSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (ActorToSpawn)
	{
		if (UWorld* world = GetWorld())
		{
			if (AActor* spawnedActor = world->SpawnActor(ActorToSpawn->GetDefaultObject()->GetClass()))
			{
				spawnedActor->SetActorLocation(UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->GetComponentLocation(), SpawnVolume->GetUnscaledBoxExtent()));
				TestTDStatics::putInCombatZPlane(spawnedActor);
			}
		}
	}
}

