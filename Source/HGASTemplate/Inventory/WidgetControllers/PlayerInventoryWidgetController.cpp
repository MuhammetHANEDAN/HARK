// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryWidgetController.h"

#include "HGASTemplate/Inventory/Components/PlayerInventoryComponent.h"

void UPlayerInventoryWidgetController::ClosePlayerInventory()
{
	if (PlayerInventoryComponent.IsValid())
	{
		PlayerInventoryComponent.Get()->ClosePlayerInventory();
	}
}
