// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"

#include "Components/WidgetComponent.h"
#include "HGASTemplate/DEBUG/HDebugTypes.h"


// Sets default values
AChest::AChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRootComponent");
	SetRootComponent(DefaultRootComponent);

	ShowMessageWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("ShowMessageWidgetComponent");
	ShowMessageWidgetComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChest::Interact_Implementation()
{
	HLOG("Chect interact Start");
}

void AChest::InteractEnd_Implementation()
{
	HLOG("Chect interact End");
}

void AChest::FInteract_Implementation(AHPlayerController* HPlayerController)
{
	HLOG("Chect F interact ");
}



