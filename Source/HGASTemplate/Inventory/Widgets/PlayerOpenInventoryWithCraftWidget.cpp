// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerOpenInventoryWithCraftWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryGrid/InventoryGrid.h"

void UPlayerOpenInventoryWithCraftWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ShowTargetInventory();

	ButtonTargetInventory->OnClicked.AddDynamic(this, &ThisClass::ShowTargetInventory);
	ButtonTargetCraft->OnClicked.AddDynamic(this, &ThisClass::ShowTargetCraft);
	
}

void UPlayerOpenInventoryWithCraftWidget::ShowTargetInventory()
{
	ButtonTargetInventory->SetIsEnabled(false);
	ButtonTargetCraft->SetIsEnabled(true);
	TargetSwitcher->SetActiveWidget(TargetInventoryGrid);
}

void UPlayerOpenInventoryWithCraftWidget::ShowTargetCraft()
{
	ButtonTargetCraft->SetIsEnabled(false);
	ButtonTargetInventory->SetIsEnabled(true);
	TargetSwitcher->SetActiveWidget(TargetCraftGrid);
}
