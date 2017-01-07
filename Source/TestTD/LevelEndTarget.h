// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "LevelEndTarget.generated.h"

/**
 * 
 */
UCLASS()
class TESTTD_API ALevelEndTarget : public ATargetPoint
{
	GENERATED_BODY()

private:

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public:
	ALevelEndTarget();

	UPROPERTY()
	UBoxComponent* endVolume;
	

	UPROPERTY(EditAnywhere)
	FName collisionProfile;
};
