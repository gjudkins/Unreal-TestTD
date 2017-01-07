// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaddieSpawner.generated.h"

UCLASS()
class TESTTD_API ABaddieSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaddieSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToSpawn;

	//UPROPERTY(EditAnywhere)
	//FName SpawnCollisionProfile;
	
	UPROPERTY()
	UBoxComponent* SpawnVolume;
};
