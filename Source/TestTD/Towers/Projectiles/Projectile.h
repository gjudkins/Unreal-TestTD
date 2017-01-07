// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TESTTD_API AProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	// this is the time that Projectile should destroy itself (for memory)
	float dieTime;

public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float speed;

	// the missile radius for collisions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float collisionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float damage;

	// the amount of time after being spawned that Projectile should live before destroying itself
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float maxLifeDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* projectileDirection;

	// the missile radius for collisions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FName movementCollisionProfile;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	//class UPaperSpriteComponent* projectileSprite;

protected:
	FTimerHandle destroyTimerHandle;

	//void Explode();

	///** What to do when the projectile explodes. The base version just destroys the projectile. */
	//UFUNCTION(BlueprintNativeEvent, Category = "Projectile")
	//void OnExplode();
	//virtual void OnExplode_Implementation();
};
