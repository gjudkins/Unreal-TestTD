// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "Baddies/BaddieCharacter.h"
#include "LevelEndTarget.h"
#include "BasicAIController.h"


ABasicAIController::ABasicAIController()
{
}

void ABasicAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (pawnAsBaddie)
	{
		if (endDestination)
		{
			//EPathFollowingRequestResult::Type result = MoveToActor(endDestination);
			MoveToActor(endDestination, 1.0f, true, true, false, 0, true);
		}
		else
		{
			locateEndDestination();
		}
	}
}

void ABasicAIController::Possess(APawn* inPawn)
{
	Super::Possess(inPawn);
	pawnAsBaddie = Cast<ABaddieCharacter>(GetPawn());
}

void ABasicAIController::UnPossess()
{
	Super::UnPossess();
	pawnAsBaddie = nullptr;
}

void ABasicAIController::locateEndDestination()
{
	if (!endDestination)
	{
		TArray<AActor*> levelActors = GetLevel()->Actors;
		for (int i = 0; i < levelActors.Num(); i++) {
			AActor* levelActor = levelActors[i];
			ALevelEndTarget* endTarget = Cast<ALevelEndTarget>(levelActor);
			if (endTarget)
			{
				endDestination = endTarget;
			}
		}
	}
}