// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HGASTemplate/UI/WidgetControllers/HWidgetController.h"
#include "PlayerInventoryWidgetController.generated.h"

class UPlayerInventoryComponent;
/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API UPlayerInventoryWidgetController : public UHWidgetController
{
	GENERATED_BODY()

public:
	
	TWeakObjectPtr<UPlayerInventoryComponent> PlayerInventoryComponent;

	UFUNCTION(BlueprintCallable)
	void ClosePlayerInventory();
	
};
