// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseInventoryComponent.h"


UBaseInventoryComponent::UBaseInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;
	
	
}

void UBaseInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UBaseInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UBaseInventoryComponent::CloseAllWidgets()
{
	
}


