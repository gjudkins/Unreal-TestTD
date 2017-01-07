// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Touchable.h"
#include "TowerBase.generated.h"

UCLASS()
class TESTTD_API ATowerBase : public APawn, public ITouchable
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleInstanceOnly, Category = "AI")
	AActor* targetActor;

	UPROPERTY(VisibleInstanceOnly, Category = "AI")
	class ABaddieCharacter* targetBaddie;
	
	float input_YawDesired;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower", meta = (ClampMin = "0.0"))
	float attackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower", meta = (ClampMin = "0.0"))
	float attackRate;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = "Tower")
	float timeNextAttackIsAvailable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower", meta = (ClampMin = "0.0"))
	float yawSpeed;

	// Sets default values for this pawn's properties
	ATowerBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// created and named on the sprite
	static const FName fireSocketName;

	UFUNCTION(BlueprintCallable, Category = "Tower")
	void didSelect() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* towerStationarySprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* towerRotatingSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* towerArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* towerBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower")
	TSubclassOf<AActor> projectileClass;

	// This can be used to start attack animations.
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void BPE_fire(float DeltaSeconds);

	//~ BEGIN AI STUFF
	//~ BEGIN AI STUFF
	//~ BEGIN AI STUFF
	UFUNCTION(BlueprintCallable, Category = "AI")
	void setTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category = "AI")
	AActor* getTarget();

	UFUNCTION(BlueprintCallable, Category = "AI")
	class ABaddieCharacter* getTargetAsBaddie();

	UFUNCTION(BlueprintCallable, Category = "AI")
	bool isTargetInRange();

	UFUNCTION(BlueprintCallable, Category = "AI")
	bool isActorInRange(AActor* target);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void fire();

	// will call this on Tick.
	UFUNCTION(BlueprintNativeEvent, Category = "AI")
	void towerAI(float DeltaSeconds);
	virtual void towerAI_Implementation(float DeltaSeconds);
	//~ END AI STUFF
	//~ END AI STUFF
	//~ END AI STUFF



	//~ BEGIN INPUT STUFF
	//~ BEGIN INPUT STUFF
	//~ BEGIN INPUT STUFF
	/** Add rotation equal to the yaw (in degrees) provided. */
	UFUNCTION(BlueprintCallable, Category = "TowerBase|Input", meta = (Keywords = "AddInput"))
	virtual void addRotationInput(float DeltaYawDegrees);

	UFUNCTION(BlueprintCallable, Category = "TowerBase|Input", meta = (Keywords = "AddInput"))
	virtual void setDesiredRotation(float DeltaYawDegrees);

	/** Get rotation input. Returns pre-clear value. */
	UFUNCTION(BlueprintCallable, Category = "TowerBase|Input", meta = (Keywords = "GetInput"))
	virtual float getRotationInput();

	/** Get (and clear) rotation input. Returns pre-clear value. */
	UFUNCTION(BlueprintCallable, Category = "TowerBase|Input", meta = (Keywords = "ConsumeInput"))
	virtual float consumeRotationInput();
	//~ END INPUT STUFF
	//~ END INPUT STUFF
	//~ END INPUT STUFF

};
