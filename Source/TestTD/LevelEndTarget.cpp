// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "Baddies/BaddieCharacter.h"
#include "LevelEndTarget.h"



ALevelEndTarget::ALevelEndTarget()
{
	PrimaryActorTick.bCanEverTick = true;

	endVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("endVolume"));
	FVector boxExtent = endVolume->GetUnscaledBoxExtent();
	boxExtent.Z = 100.0f;
	endVolume->SetBoxExtent(boxExtent, false);
	if (RootComponent)
	{
		endVolume->SetupAttachment(RootComponent);
	}
	else
	{
		RootComponent = endVolume;
	}

	collisionProfile = TEXT("LevelEnd");
}

// Called every frame
void ALevelEndTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UWorld* world = GetWorld())
	{
		/*FCollisionShape collisionShape;
		collisionShape.SetBox(endVolume->GetUnscaledBoxExtent());*/
		//world->OverlapAnyTestByProfile()

		TArray<FOverlapResult> overlapResults;
		FVector boxSize = endVolume->GetScaledBoxExtent();

		FCollisionShape collisionShape;
		collisionShape.SetBox(boxSize);
		//world->OverlapMultiByProfile(hitResults,endVolume->GetComponentLocation())
		world->OverlapMultiByProfile(overlapResults, endVolume->GetComponentLocation(), endVolume->GetComponentRotation().Quaternion(), collisionProfile, collisionShape);
		
		for (const FOverlapResult& overlapResult : overlapResults)
		{
			if (ABaddieCharacter* baddie = Cast<ABaddieCharacter>(overlapResult.Actor.Get()))
			{
				baddie->didReachLevelEnd();
			}
		}

	}
}
