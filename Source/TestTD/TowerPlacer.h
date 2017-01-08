// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Touchable.h"
#include "TowerPlacer.generated.h"

UENUM(BlueprintType)
enum class ETowerType : uint8
{
	TypeA,
	TypeB,
	TypeC,
	TypeD
};

UCLASS()
class TESTTD_API ATowerPlacer : public AActor, public ITouchable
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TowerPlacer", meta = (AllowPrivateAccess = "true"))
	bool bIsShowingButtons = false;

public:
	// Sets default values for this actor's properties
	ATowerPlacer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	void Destroy();
	//UFUNCTION(BlueprintImplementableEvent)
	//void didSelect();

	//UFUNCTION(BlueprintImplementableEvent)
	//void hideTowerSelector();
	
	UFUNCTION(BlueprintCallable, Category = "TowerPlacer")
	void didSelectTower(ETowerType towerType);

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "TowerPlacer")
	//void createTowerSelectorWidget();

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "TowerPlacer")
	//void getLocationOnScreen();
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerPlacer", meta = (AllowPrivateAccess = "true"))
	//FVector2D locationOnScreen;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerPlacer", meta = (AllowPrivateAccess = "true"))
	//class UTowerPlacerSelectorHUD* towerSelectorWidget;

	UFUNCTION(BlueprintCallable, Category = "TowerPlacer")
	void deselectAllTowerPlacers();

	UFUNCTION(BlueprintCallable, Category = "TowerPlacer")
	void didSelect() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerPlacer", meta = (AllowPrivateAccess = "true"))
	TArray<class UPaperSprite*> spriteIcons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerPlacer", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* towerPlacerSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TowerPlacer", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* towerPlacerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerPlacer", meta = (AllowPrivateAccess = "true"))
	TArray<ETowerType> availableTowers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerPlacer", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<APawn>> availableTowerClasses;

	UFUNCTION(BlueprintCallable, Category = "TowerPlacer")
	void setAvailableTowers(TArray<ETowerType> _availableTowers);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TowerPlacer", meta = (AllowPrivateAccess = "true"))
	TArray<class ATowerPlacerButton*> towerButtons;

	UFUNCTION(BlueprintCallable, Category = "TowerPlacer")
	void showTowerButtons();

	UFUNCTION(BlueprintCallable, Category = "TowerPlacer")
	void hideTowerButtons();

	UFUNCTION(BlueprintCallable, Category = "TowerPlacer")
	void positionTowerButtons();

	UFUNCTION(BlueprintCallable, Category = "TowerPlacer")
	float getScaleDifferenceWithActor(AActor* actor, bool reverse = false);

	UFUNCTION(BlueprintCallable, Category = "TowerPlacer")
	float getWidth(AActor* actor);
};
