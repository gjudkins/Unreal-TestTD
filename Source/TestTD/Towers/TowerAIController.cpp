// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "Towers/TowerBase.h"
#include "TowerAIController.h"


void ATowerAIController::Tick(float DeltaTime)
{
	if (pawnAsTower)
	{
		if (AActor* Target = pawnAsTower->getTarget())
		{
			// We do have a target. Shamble toward it and attempt violence!
			FVector DirectionToTarget = (Target->GetActorLocation() - pawnAsTower->GetActorLocation()).GetSafeNormal2D();
			FVector forwardDirection = pawnAsTower->towerArrowComponent->GetForwardVector();
			FVector rightDirection = pawnAsTower->towerArrowComponent->GetRightVector();
			
			// DotProduct gives the Cos between two angles
			float DotToTarget = FVector::DotProduct(DirectionToTarget, forwardDirection);//pawnAsTower->GetActorForwardVector()
			float SidewaysDotToTarget = FVector::DotProduct(DirectionToTarget, rightDirection);//pawnAsTower->GetActorRightVector()
			float DeltaYawDesired = FMath::Atan2(SidewaysDotToTarget, DotToTarget);
			DeltaYawDesired *= 10;

			// Attempt the entire turn in one frame. The Tower itself will cap this, we're only expressing our desired turn amount here.
			pawnAsTower->setDesiredRotation(DeltaYawDesired);
		}

	}
}
void ATowerAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	pawnAsTower = Cast<ATowerBase>(GetPawn());
}

void ATowerAIController::UnPossess()
{
	Super::UnPossess();
}
