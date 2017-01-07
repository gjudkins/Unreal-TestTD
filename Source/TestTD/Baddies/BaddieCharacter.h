// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaddieCharacter.generated.h"

UCLASS()
class TESTTD_API ABaddieCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool bDidReachLevelEnd = false;
public:
	// Sets default values for this character's properties
	ABaddieCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Baddie", meta = (AllowPrivateAccess = "true"))
	class UCharacterMovementComponent* movement;
	
	//UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void didReachLevelEnd();
};
