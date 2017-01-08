// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTD.h"
#include "PaperSpriteComponent.h"
#include "TowerPlacer.h"
#include "TowerPlacerButton.h"


// Sets default values
ATowerPlacerButton::ATowerPlacerButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = buttonBox = CreateDefaultSubobject<UBoxComponent>(TEXT("towerPlacerButtonBox"));
		
	//towerPlacerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RootComponent->GetAttachSocketName());ame());

	buttonSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("towerPlacerButtonSprite"));
	buttonSprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, RootComponent->GetAttachSocketName());

	//static ConstructorHelpers::FObjectFinder<UPaperSprite> towerAIcon(TEXT("PaperSprite'/Game/Sprites/Terrain/tilesheet_complete_2X_Terrain_196.tilesheet_complete_2X_Terrain_196'"));
	//static ConstructorHelpers::FObjectFinder<UPaperSprite> towerBIcon(TEXT("PaperSprite'/Game/Sprites/Terrain/tilesheet_complete_2X_Terrain_318.tilesheet_complete_2X_Terrain_318'"));
	//static ConstructorHelpers::FObjectFinder<UPaperSprite> towerCIcon(TEXT("PaperSprite'/Game/Sprites/Terrain/tilesheet_complete_2X_Terrain_449.tilesheet_complete_2X_Terrain_196'"));
	//static ConstructorHelpers::FObjectFinder<UPaperSprite> towerDIcon(TEXT("PaperSprite'/Game/Sprites/Terrain/tilesheet_complete_2X_Terrain_535.tilesheet_complete_2X_Terrain_196'"));

	//switch (towerType)
	//{
	//case ETowerType::TypeA:
	//	buttonSprite->SetSprite(towerAIcon.Object);
	//	break;
	//case ETowerType::TypeB:
	//	buttonSprite->SetSprite(towerBIcon.Object);
	//	break;
	//case ETowerType::TypeC:
	//	buttonSprite->SetSprite(towerCIcon.Object);
	//	break;
	//case ETowerType::TypeD:
	//	buttonSprite->SetSprite(towerDIcon.Object);
	//	break;
	//}

}

// Called when the game starts or when spawned
void ATowerPlacerButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerPlacerButton::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATowerPlacerButton::didSelect()
{
	UE_LOG(LogTemp, Warning, TEXT("ATowerPlacerButton::didSelect()"));
	onTowerSelected.Broadcast(towerType);
}