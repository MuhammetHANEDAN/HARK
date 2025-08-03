// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryWidget.h"
#include "PlayerOpenInventoryNoCraftWidget.generated.h"

/**
 * Etkileşimle açılan envanterin craft bölümü olmayacak
 */
UCLASS()
class HGASTEMPLATE_API UPlayerOpenInventoryNoCraftWidget : public UBaseInventoryWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> TargetInventoryGrid;
};
