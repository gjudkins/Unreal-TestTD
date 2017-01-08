// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class TESTTD_API TestTDStatics
{
public:
	TestTDStatics();
	~TestTDStatics();

public:

	UFUNCTION(BlueprintCallable, Category = "Statics")
	static float getCombatZPlane() { return -300.0f; };

	UFUNCTION(BlueprintCallable, Category = "Statics")
	static float getUIZPlane() { return 0.0f; };
	
	/** Calculate angle difference in the range [-180, 180]. */
	UFUNCTION(BlueprintCallable, Category = "Math")
	static float FindDeltaAngleDegrees(float A1, float A2);

	/** Finds the angle between two 2D points. */
	UFUNCTION(BlueprintPure, Category = "Math|Rotator", meta = (Keywords = "rotation rotate"))
	static bool FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle);

	/** Get the current game mode, pre-cast to ATanksGameMode for convenience. */
	UFUNCTION(BlueprintCallable, Category = "Statics")
	static class ABasicGameMode* GetBasicGameMode(UObject* WorldContextObject);

	/** Snap this actor to the Z plane that we're using for this level. */
	UFUNCTION(BlueprintCallable, Category = "Statics")
	static void putInCombatZPlane(AActor* ActorToMove);

	UFUNCTION(BlueprintCallable, Category = "Statics")
	static void putInUIZPlane(AActor* ActorToMove);

	/** All-in-one convenience function to play a flipbook. */
	//UFUNCTION(BlueprintCallable, Category = "Animation")
	//static void PlayFlipbook(class UPaperFlipbookComponent* Component, class UPaperFlipbook* NewFlipbook, bool bLooping, float PlayRate = 1.0f, bool bPlayFromStart = false);
};
