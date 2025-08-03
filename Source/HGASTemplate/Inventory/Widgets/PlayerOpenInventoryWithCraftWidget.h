// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryWidget.h"
#include "PlayerOpenInventoryWithCraftWidget.generated.h"

/**
 * Etkileşimle açılan envanterin craft bölümü olacak
 */
UCLASS()
class HGASTEMPLATE_API UPlayerOpenInventoryWithCraftWidget : public UBaseInventoryWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> TargetSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> TargetInventoryGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> TargetCraftGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonTargetInventory;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonTargetCraft;

	UFUNCTION()
	void ShowTargetInventory();

	UFUNCTION()
	void ShowTargetCraft();
	
};
