// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "PaperSpriteComponent.h"
#include "Towers/TowerPlacerButton.h"
#include "TestTDStatics.h"
#include "TowerPlacer.h"

// Sets default values
ATowerPlacer::ATowerPlacer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TowerPlacerBase"));
	}

	towerPlacerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("towerPlacerBox"));
	towerPlacerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RootComponent->GetAttachSocketName());
	//towerPlacerSprite->AttachToComponent(TankDirection, FAttachmentTransformRules::KeepRelativeTransform, towerPlacerSprite->GetAttachSocketName());

	towerPlacerSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("towerPlacerSprite"));
	towerPlacerSprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RootComponent->GetAttachSocketName());
	//towerPlacerSprite->AddRelativeRotation(FQuat(FRotator(0.0f, 0.0f, -90.0f)));
	//towerPlacerSprite->AddWorldRotation(FQuat(FRotator(0.0f, 0.0f, -90.0f)));
	//towerPlacerSprite->AddLocalRotation(FQuat(FRotator(0.0f, 0.0f, -90.0f)));

	static ConstructorHelpers::FObjectFinder<UPaperSprite> towerAIcon(TEXT("PaperSprite'/Game/Sprites/UI/Towers_towers_277.Towers_towers_277'"));
	spriteIcons.Add(towerAIcon.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> towerBIcon(TEXT("PaperSprite'/Game/Sprites/UI/Towers_towers_278.Towers_towers_278'"));
	spriteIcons.Add(towerBIcon.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> towerCIcon(TEXT("PaperSprite'/Game/Sprites/UI/Towers_towers_279.Towers_towers_279'"));
	spriteIcons.Add(towerCIcon.Object);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> towerDIcon(TEXT("PaperSprite'/Game/Sprites/UI/Towers_towers_280.Towers_towers_280'"));
	spriteIcons.Add(towerDIcon.Object);
}
void ATowerPlacer::Destroy()
{
	hideTowerButtons();

	Super::Destroy();
}

// Called when the game starts or when spawned
void ATowerPlacer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerPlacer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATowerPlacer::didSelect()
{
	UE_LOG(LogTemp, Warning, TEXT("ATowerPlacer::didSelect()"));
	if (bIsShowingButtons)
	{
		hideTowerButtons();
	} else
	{
		showTowerButtons();
	}
}

void ATowerPlacer::setAvailableTowers(TArray<ETowerType> _availableTowers)
{
	availableTowers = _availableTowers;
}

void ATowerPlacer::showTowerButtons()
{	
	// make sure that this towerplacer is the only one with a menu open
	deselectAllTowerPlacers();

	availableTowers = { ETowerType::TypeA, ETowerType::TypeB, ETowerType::TypeC, ETowerType::TypeD };

	if (UWorld* world = GetWorld())
	{

		FVector location = towerPlacerBox->GetComponentLocation();
		location.Y -= getWidth(this);
		FRotator rotation = FRotator(0.0f, 0.0f, -90.0f); // to get the 2d sprite facing the camera
			
		FActorSpawnParameters spawnInfo;
		spawnInfo.Owner = this;

		for (int i = 0; i < availableTowers.Num(); i++)
		{
			if (ATowerPlacerButton* spawnedActor = world->SpawnActor<ATowerPlacerButton>(location, rotation, spawnInfo))
			{
				spawnedActor->towerType = availableTowers[i];
				spawnedActor->buttonSprite->SetSprite(spriteIcons[i]);
				towerButtons.Add(spawnedActor);
				
				float scaleFactor = getScaleDifferenceWithActor(spawnedActor);
				spawnedActor->SetActorScale3D(FVector(scaleFactor));

				//TestTDStatics::PutInZPlane(spawnedActor);
			}
		}
	}

	positionTowerButtons();

	bIsShowingButtons = true;
}

void ATowerPlacer::positionTowerButtons()
{
	FVector placerLocation = towerPlacerBox->GetComponentLocation();
	float placerWidth = getWidth(this);

	int numButtons = towerButtons.Num();

	float newY = placerLocation.Y - placerWidth;
	float totalWidth = numButtons * placerWidth;

	for (int i = 0; i < numButtons; i++) {
		if (ATowerPlacerButton* button = towerButtons[i])
		{
			float newX = (placerLocation.X - (totalWidth / 2) + (placerWidth / 2)) + (placerWidth * ((float)i));
			FVector newLocation;
			newLocation.Y = newY;
			newLocation.X = newX;
			button->SetActorLocation(newLocation);

			TestTDStatics::PutInZPlane(button);
		}
	}
}

void ATowerPlacer::hideTowerButtons()
{
	for (int i = 0; i < towerButtons.Num(); i++) {
		if (ATowerPlacerButton* button = towerButtons[i])
		{
			button->Destroy();
			//button->SetActorHiddenInGame(true);
		}
	}
	towerButtons.Empty();
	bIsShowingButtons = false;
}

float ATowerPlacer::getScaleDifferenceWithActor(AActor* actor)
{
	float width = getWidth(this);

	float actorWidth = getWidth(actor);

	float scaleFactor = width / actorWidth;

	return scaleFactor;
}

float ATowerPlacer::getWidth(AActor* actor)
{
	if (!actor)
	{
		actor = this;
	}
	FVector extent;
	FVector origin;
	actor->GetActorBounds(false, origin, extent);
	extent *= 2;

	return extent.X;
}

void ATowerPlacer::deselectAllTowerPlacers()
{
	TArray<AActor*> allTowerPlacerActors;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATowerPlacer::StaticClass(), allTowerPlacerActors);

	//UE_LOG(LogTemp, Warning, TEXT("000000"));
	for (int i = 0; i < allTowerPlacerActors.Num(); i++) {
		if (ATowerPlacer* towerPlacer = Cast<ATowerPlacer>(allTowerPlacerActors[i]))
		{
			towerPlacer->hideTowerButtons();
		}
	}
}