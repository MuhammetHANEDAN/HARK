// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryWidget.h"
#include "PlayerOpenInventoryCreatureWidget.generated.h"

/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API UPlayerOpenInventoryCreatureWidget : public UBaseInventoryWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryGrid> CreatureInventoryGrid;

	
};
