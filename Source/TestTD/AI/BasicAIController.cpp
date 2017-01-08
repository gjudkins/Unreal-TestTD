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

			float dist = getPathDistanceToTarget();
		}
		else
		{
			locateEndDestination();
		}
	}
}
float ABasicAIController::getPathDistanceToTarget() {
	float dist = GetPathFollowingComponent()->GetRemainingPathCost();

	if (dist == 0 && pawnAsBaddie && endDestination)
	{
		dist = pawnAsBaddie->GetDistanceTo(endDestination);
	}

	return dist;
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
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelEndTarget::StaticClass(), foundActors);

		for (int i = 0; i < foundActors.Num(); i++) {
			AActor* foundActor = foundActors[i];
			ALevelEndTarget* endTarget = Cast<ALevelEndTarget>(foundActor);
			if (endTarget)
			{
				endDestination = endTarget;
				break;
			}
		}
	}
}