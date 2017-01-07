// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "TowerPlacer.h"
#include "Touchable.h"
#include "CustomCameraComponent.h"
#include "PlayerInputPawn.h"


// Sets default values
APlayerInputPawn::APlayerInputPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("InputBase"));
	}

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//SpringArm->TargetArmLength = 1000.0f;
	//SpringArm->bEnableCameraLag = true;
	//SpringArm->bEnableCameraRotationLag = false;
	//SpringArm->bUsePawnControlRotation = false;
	//SpringArm->CameraLagSpeed = 0.0;
	//SpringArm->bDoCollisionTest = false;
	//SpringArm->SetupAttachment(RootComponent);
	//SpringArm->SetWorldRotation(FRotator(-90.0, 0.0, 0.0));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 1024.0f * 2.0f;
	CameraComponent->AspectRatio = 9.0f / 16.0f;
	//CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetWorldRotation(FRotator(-90.0, -90.0f, 0.0));

}

// Called when the game starts or when spawned
void APlayerInputPawn::BeginPlay()
{
	Super::BeginPlay();
	//APlayerController* PlayerController = Cast<APlayerController>(GetController());
	playerController = UGameplayStatics::GetPlayerController(this, 0);
}
void APlayerInputPawn::OnTouchBegin(ETouchIndex::Type touchType, FVector _newTouchLocation)
{
	if (touchType == ETouchIndex::Touch1) {
		if (playerController)
		{
			bool bIsCurrentlyPressed;
			playerController->GetInputTouchState(ETouchIndex::Touch1, previousTouchLocation.X, previousTouchLocation.Y, bIsCurrentlyPressed);
		}
	}
}
// Called every frame
void APlayerInputPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (playerController)
	{
		bool bIsCurrentlyPressed;
		playerController->GetInputTouchState(ETouchIndex::Touch1, newTouchLocation.X, newTouchLocation.Y, bIsCurrentlyPressed);

		if (bIsCurrentlyPressed)
		{
			FVector2D deltaTouchLocation = newTouchLocation - previousTouchLocation;

			deltaTouchLocation.X *= -1.0f;
			deltaTouchLocation.Y *= -1.0f;

			FVector deltaOffset = FVector(deltaTouchLocation.X, deltaTouchLocation.Y, 0.0f);

			this->AddActorWorldOffset(deltaOffset);

			previousTouchLocation = newTouchLocation;
		}
	}
	
}

// Called to bind functionality to input
void APlayerInputPawn::SetupPlayerInputComponent(class UInputComponent* IC)
{
	Super::SetupPlayerInputComponent(IC);

	IC->BindAction("BasicTouch", EInputEvent::IE_Pressed, this, &APlayerInputPawn::HandleBasicTouch);
	IC->BindTouch(EInputEvent::IE_Pressed, this, &APlayerInputPawn::OnTouchBegin);
}

void APlayerInputPawn::HandleBasicTouch(FKey key)
{
	//TChar* name = key.GetDisplayName().ToString().GetCharArray();
	//UE_LOG(LogTemp, Warning, name);
	//UE_LOG(LogTemp, Warning, TEXT("name: %s"), key.GetDisplayName().ToString().GetCharArray());

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		// Get the coordinates of the mouse from our controller  
		float LocationX;
		float LocationY;
		PlayerController->GetMousePosition(LocationX, LocationY);
		
		// Do a trace and see if there the position intersects something in the world  
		FVector2D MousePosition(LocationX, LocationY);
		FHitResult HitResult;
		const bool bTraceComplex = false;
		//PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_EngineTraceChannel5, false, HitResult)
		if (PlayerController->GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, bTraceComplex, HitResult) == true)
		{

			ITouchable* touchableObject = Cast<ITouchable>(HitResult.GetActor());
			//ATowerPlacer* TowerPlacer = Cast<ATowerPlacer>(HitResult.GetActor());
			if (touchableObject)
			{
				touchableObject->didSelect();
				//TowerPlacer->didSelect();
				//UE_LOG(LogTemp, Warning, TEXT("Touched a TowerPlacer!!!!"));
			}

			//APawn* ClickedPawn = Cast<APawn>(HitResult.GetActor());
			//if (ClickedPawn != nullptr)
			//{
			//	// Unposses ourselves  
			//	PlayerController->UnPossess();
			//	// Posses the controller we clicked on  
			//	PlayerController->Possess(ClickedPawn);
			//}
		}

	}

}

void APlayerInputPawn::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{
	/*FVector WorldPosition(0.f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	{
		IStrategyInputInterface::Execute_OnInputTap(HitActor);
	}*/
}

void APlayerInputPawn::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{
	/*FVector WorldPosition(0.0f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	{
		IStrategyInputInterface::Execute_OnInputHold(HitActor);
	}*/
}

void APlayerInputPawn::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{
	/*AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	{
		IStrategyInputInterface::Execute_OnInputHoldReleased(Selected, DownTime);
	}*/
}

void APlayerInputPawn::OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime)
{
	//if (SpringArm)
	//{
	//	//GetCameraComponent()->OnSwipeStarted(AnchorPosition);
	//}

	FVector WorldPosition(0.0f);
	//AActor* const HitActor = GetFriendlyTarget(AnchorPosition, WorldPosition);

	//SetSelectedActor(HitActor, WorldPosition);

	///** Get our position in 3d space */
	//if (SelectedActor.IsValid())
	//{
	//	SwipeAnchor3D = SelectedActor->GetActorLocation();
	//}

	PrevSwipeScreenPosition = AnchorPosition;
}

void APlayerInputPawn::OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime)
{
	/*AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	{
		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0, 0, 1));

		FVector RayOrigin, RayDirection;
		FStrategyHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = FStrategyHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		IStrategyInputInterface::Execute_OnInputSwipeUpdate(Selected, ScreenPosition3D - SwipeAnchor3D);
	}
	else
	{
		if (GetCameraComponent() != NULL)
		{
			GetCameraComponent()->OnSwipeUpdate(ScreenPosition);
		}
	}

	PrevSwipeScreenPosition = ScreenPosition;*/
}

void APlayerInputPawn::OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime)
{
	/*AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	{
		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(this->Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0, 0, 1));

		FVector RayOrigin, RayDirection;
		FStrategyHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = FStrategyHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		IStrategyInputInterface::Execute_OnInputSwipeReleased(Selected, ScreenPosition3D - SwipeAnchor3D, DownTime);
	}
	else
	{
		if (GetCameraComponent() != NULL)
		{
			GetCameraComponent()->OnSwipeReleased(ScreenPosition);
		}
	}*/
}
void APlayerInputPawn::OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	/*if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchStarted(AnchorPosition1, AnchorPosition2, DownTime);
	}*/
}

void APlayerInputPawn::OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	/*if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchUpdate(InputHandler, ScreenPosition1, ScreenPosition2, DownTime);
	}*/
}
