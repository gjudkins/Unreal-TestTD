// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "BasicGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTTD_API ABasicGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ABasicGameMode();

public:

	UPROPERTY(EditAnywhere)
	float PlayInZPlane;
	
	
};
