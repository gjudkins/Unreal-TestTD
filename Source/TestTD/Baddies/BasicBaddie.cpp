// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "BasicBaddie.h"

// Sets default values
ABasicBaddie::ABasicBaddie()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baddieType = EBaddieType::Red;
}

// Called when the game starts or when spawned
void ABasicBaddie::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasicBaddie::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABasicBaddie::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

