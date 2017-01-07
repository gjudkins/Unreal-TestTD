// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "PaperSpriteComponent.h"
#include "TestTDStatics.h"
#include "Towers/Projectiles/Projectile.h"
#include "Baddies/BaddieCharacter.h"
#include "TowerBase.h"


const FName ATowerBase::fireSocketName(TEXT("fireSocket"));
// Sets default values
ATowerBase::ATowerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TowerSceneComponent"));
	}

	towerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("towerBox"));
	towerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RootComponent->GetAttachSocketName());
	//towerPlacerSprite->AttachToComponent(TankDirection, FAttachmentTransformRules::KeepRelativeTransform, towerPlacerSprite->GetAttachSocketName());

	towerStationarySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("towerStationarySprite"));
	towerStationarySprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RootComponent->GetAttachSocketName());

	towerArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("towerArrowComponent"));
	towerArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RootComponent->GetAttachSocketName());

	towerRotatingSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("towerRotatingSprite"));
	towerRotatingSprite->AttachToComponent(towerArrowComponent, FAttachmentTransformRules::KeepRelativeTransform, towerArrowComponent->GetAttachSocketName());

	yawSpeed = 250.0f;
	attackRange = 300.0f;
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// if the target has gone out of range, forget about it.
	if (!isTargetInRange())
	{
		setTarget(nullptr);
	}

	// perform ai logic before consuming (destroying) the input.
	towerAI(DeltaTime);

	consumeRotationInput();
}

// Called to bind functionality to input
void ATowerBase::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

}

void ATowerBase::addRotationInput(float DeltaYawDegrees) {
	input_YawDesired += DeltaYawDegrees;
}
void ATowerBase::setDesiredRotation(float DeltaYawDegrees) {
	input_YawDesired = DeltaYawDegrees;
}
float ATowerBase::getRotationInput() {
	return input_YawDesired;
}
float ATowerBase::consumeRotationInput() {
	float RetVal = input_YawDesired;
	input_YawDesired = 0.0f;
	return RetVal;
}

void ATowerBase::didSelect()
{
	UE_LOG(LogTemp, Warning, TEXT("ATowerBase::didSelect()"));
}


void ATowerBase::setTarget(AActor* NewTarget)
{
	targetActor = NewTarget;
	targetBaddie = Cast<ABaddieCharacter>(NewTarget);
}

AActor* ATowerBase::getTarget()
{
	return targetActor;
}

ABaddieCharacter* ATowerBase::getTargetAsBaddie()
{
	return targetBaddie;
}

bool ATowerBase::isActorInRange(AActor* target)
{
	if (target)
	{
		// Attack our target if we're in range. For now, we'll use our unmodified attack variables for this.
		FVector OurLocation = GetActorLocation();
		float DistSqXY = FVector::DistSquaredXY(target->GetActorLocation(), OurLocation);
		if (DistSqXY <= (attackRange * attackRange))
		{
			// Note that attacking cooldown isn't checked. We don't want this kind of zombie to move between attacks or think it's not attacking while waiting for the cooldown.
			return true;
		}
	}
	return false;
}
bool ATowerBase::isTargetInRange()
{
	return isActorInRange(getTarget());
}
void ATowerBase::towerAI_Implementation(float DeltaSeconds)
{
	// rotate the tower before firing the bullet (aim before shooting)
	float MaxYawThisFrame = yawSpeed * DeltaSeconds;

	FRotator DesiredRot = towerArrowComponent->GetComponentRotation() + FRotator(0.0f, FMath::Clamp(getRotationInput(), -MaxYawThisFrame, MaxYawThisFrame), 0.0f);
	towerArrowComponent->SetWorldRotation(DesiredRot.Quaternion());


	if (AActor* Target = getTarget())
	{

		// TODO: maybe put this in a 
		FVector DirectionToTarget = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
		FVector forwardDirection = towerArrowComponent->GetForwardVector();
		FQuat between = FQuat::FindBetweenVectors(DirectionToTarget, forwardDirection);
		FRotator rAngle(between);
		float angle = FMath::Abs(rAngle.Yaw);
		
		float CurrentTime = GetWorld()->GetTimeSeconds();
		// this max yaw check is assuming that the rotation input (input_DesiredYaw) is the full yaw to the target (which is the case)
		bool canFire = ((angle < 15.0f) && (timeNextAttackIsAvailable <= CurrentTime) && isTargetInRange());
		if (canFire)
		{
			timeNextAttackIsAvailable = CurrentTime + attackRate;

			BPE_fire(DeltaSeconds);
			fire();

		}
	}
	else
	{

		TArray<AActor*> allTowerPlacerActors;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaddieCharacter::StaticClass(), allTowerPlacerActors);


		for (int i = 0; i < allTowerPlacerActors.Num(); i++)
		{
			AActor* actor = allTowerPlacerActors[i];
			if (isActorInRange(actor))
			{
				setTarget(actor);
				break;
			}
		}

		//for (int i = allTowerPlacerActors.Num() - 1; i >= 0; i--)
		//{
		//	AActor* actor = allTowerPlacerActors[i];
		//	if (isActorInRange(actor))
		//	{
		//		setTarget(actor);
		//	}
		//}


		// TODO: see if there are any baddies within attackRange and set the approriate target.

		// Look for a target. We might not do this every single frame, but for now it's OK.
		//Target = UGameplayStatics::GetPlayerPawn(this, 0);
		//float DistSqXY = FVector::DistSquaredXY(Target->GetActorLocation(), GetActorLocation());
		//if (DistSqXY <= (attackRange * attackRange))
		//{
		//	FVector DirectionToTarget = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
		//	if (FVector::DotProduct(DirectionToTarget, GetActorForwardVector()) >= FMath::Cos(FMath::DegreesToRadians(360.0f)))
		//	{
		//		SetTarget(Target);
		//	}
		//}
	}

	// TODO: if there is no target and no baddies in range, do some basic animation stuff to not be boring
}


void ATowerBase::fire()
{
	if (UWorld* world = GetWorld())
	{
		FVector Loc = towerRotatingSprite->GetSocketLocation(fireSocketName);
		FRotator Rot = towerArrowComponent->GetComponentRotation();

		if (AActor* NewProjectile = world->SpawnActor(projectileClass))
		{
			NewProjectile->SetActorLocation(Loc);
			NewProjectile->SetActorRotation(Rot);
			TestTDStatics::PutInZPlane(NewProjectile);
		}
	}
}