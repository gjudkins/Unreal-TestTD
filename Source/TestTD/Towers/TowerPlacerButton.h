// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Touchable.h"
#include "TowerPlacer.h"
#include "TowerPlacerButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTowerSelected, ETowerType, typeSelected);

UCLASS()
class TESTTD_API ATowerPlacerButton : public AActor, public ITouchable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerPlacerButton();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "TowerPlacerButton")
	void didSelect() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TowerPlacerButton", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* buttonSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TowerPlacerButton", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* buttonBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TowerPlacerButton", meta = (AllowPrivateAccess = "true"))
	ETowerType towerType = ETowerType::TypeA;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "TowerPlacerDelegate", meta = (AllowPrivateAccess = "true"))
	FOnTowerSelected onTowerSelected;
};
