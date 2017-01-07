// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BasicAIController.generated.h"


/**
 * 
 */
UCLASS()
class TESTTD_API ABasicAIController : public AAIController
{
	GENERATED_BODY()

private:

	class ALevelEndTarget* endDestination;

public:
	ABasicAIController();

	virtual void Tick(float DeltaTime) override;

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	void locateEndDestination();
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	class ABaddieCharacter* pawnAsBaddie;

};
