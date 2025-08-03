// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryComponent.h"

#include "HGASTemplate/Inventory/WidgetControllers/PlayerInventoryWidgetController.h"
#include "HGASTemplate/Inventory/Widgets/PlayerInventoryWidget.h"
#include "HGASTemplate/Inventory/Widgets/PlayerOpenInventoryWidget.h"


UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UPlayerInventoryComponent::ConstructInventoryWidget(const FWidgetControllerParams& WCParams)
{
	PlayerInventoryWidget = CreateWidget<UPlayerInventoryWidget>(WCParams.PlayerController,PlayerInventoryWidgetClass);
	PlayerInventoryWidget->SetWidgetController(GetPlayerInventoryWidgetController(WCParams));
	PlayerInventoryWidget->AddToViewport();
}

UPlayerInventoryWidgetController* UPlayerInventoryComponent::GetPlayerInventoryWidgetController(const FWidgetControllerParams& WCParams)
{
	if (PlayerInventoryWidgetController == nullptr)
	{
		UPlayerInventoryWidgetController* WC = NewObject<UPlayerInventoryWidgetController>(this,PlayerInventoryWidgetControllerClass);
		WC->SetWidgetControllerParams(WCParams);
	}
	return PlayerInventoryWidgetController;
}

void UPlayerInventoryComponent::CloseAllWidgets()
{
	if (!OwnerPlayerController.IsValid()) return;

	if (PlayerOpenInventoryWidget.IsValid())
	{
		PlayerOpenInventoryWidget.Get()->RemoveFromParent();
	}

	if (IsValid(PlayerInventoryWidget))
	{
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		bPlayerInventoryOpen = false;
	}
	
	FInputModeGameOnly InputMode;
	OwnerPlayerController->SetInputMode(InputMode);
	OwnerPlayerController->SetShowMouseCursor(false);
}

void UPlayerInventoryComponent::OpenPlayerInventory()
{
	if (!IsValid(PlayerInventoryWidget)) return;

	PlayerInventoryWidget->SetVisibility(ESlateVisibility::Visible);
	bPlayerInventoryOpen  = true;

	if (!OwnerPlayerController.IsValid()) return;

	FInputModeGameAndUI InputMode;
	OwnerPlayerController->SetInputMode(InputMode);
	OwnerPlayerController->SetShowMouseCursor(true);
}

void UPlayerInventoryComponent::ClosePlayerInventory()
{
	if (!IsValid(PlayerInventoryWidget)) return;

	PlayerInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	bPlayerInventoryOpen = false;

	if (!OwnerPlayerController.IsValid()) return;

	FInputModeGameOnly InputMode;
	OwnerPlayerController->SetInputMode(InputMode);
	OwnerPlayerController->SetShowMouseCursor(false);
}

void UPlayerInventoryComponent::TogglePlayerInventory()
{
	if (bPlayerInventoryOpen == false)
	{
		OpenPlayerInventory();
	}
	else
	{
		ClosePlayerInventory();
	}
}



