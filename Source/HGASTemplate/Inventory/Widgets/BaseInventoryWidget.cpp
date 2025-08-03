// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInventoryWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryGrid/InventoryGrid.h"

void UBaseInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ShowPlayerInventory();
	
	ButtonPlayerInventory->OnClicked.AddDynamic(this, &ThisClass::ShowPlayerInventory);
	ButtonPlayerCraft->OnClicked.AddDynamic(this, &ThisClass::ShowPlayerCraft);
}

void UBaseInventoryWidget::ShowPlayerInventory()
{
	ButtonPlayerInventory->SetIsEnabled(false);
	ButtonPlayerCraft->SetIsEnabled(true);
	PlayerSwitcher->SetActiveWidget(PlayerInventoryGrid);
}

void UBaseInventoryWidget::ShowPlayerCraft()
{
	ButtonPlayerCraft->SetIsEnabled(false);
	ButtonPlayerInventory->SetIsEnabled(true);
	PlayerSwitcher->SetActiveWidget(PlayerCraftGrid);
}
