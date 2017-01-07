// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BasicBaddie.generated.h"

UENUM(BlueprintType)
enum class EBaddieType : uint8
{
	Red,
	Blue,
	Green
};
UCLASS()
class TESTTD_API ABasicBaddie : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicBaddie();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Baddie", meta = (AllowPrivateAccess = "true"))
	EBaddieType baddieType;
	
};
