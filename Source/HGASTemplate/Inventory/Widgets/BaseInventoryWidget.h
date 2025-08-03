// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HGASTemplate/UI/Widget/HUserWidget.h"
#include "BaseInventoryWidget.generated.h"

class UButton;
class UInventoryGrid;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API UBaseInventoryWidget : public UHUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> PlayerSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> PlayerInventoryGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> PlayerCraftGrid;

	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonPlayerInventory;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonPlayerCraft;

	UFUNCTION()
	void ShowPlayerInventory();

	UFUNCTION()
	void ShowPlayerCraft();
	
	

	
};
