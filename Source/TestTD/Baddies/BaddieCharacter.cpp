// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "AI/BasicAIController.h"
#include "BaddieCharacter.h"


// Sets default values
ABaddieCharacter::ABaddieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	movement = GetCharacterMovement();

	movement->MaxWalkSpeed = 200.0f;

}

// Called when the game starts or when spawned
void ABaddieCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaddieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaddieCharacter::didReachLevelEnd()
{
	if (!bDidReachLevelEnd)
	{
		bDidReachLevelEnd = true;
		Destroy();
	}
}

// Called to bind functionality to input
void ABaddieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

