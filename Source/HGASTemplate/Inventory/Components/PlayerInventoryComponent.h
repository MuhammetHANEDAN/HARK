// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryComponent.h"
#include "PlayerInventoryComponent.generated.h"


class UPlayerOpenInventoryCreatureWidget;
class UPlayerOpenInventoryNoCraftWidget;
struct FWidgetControllerParams;
class UPlayerInventoryWidgetController;
class UPlayerOpenInventoryWithCraftWidget;
class UPlayerInventoryWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HGASTEMPLATE_API UPlayerInventoryComponent : public UBaseInventoryComponent
{
	GENERATED_BODY()

public:
	
	UPlayerInventoryComponent();

protected:
	
	virtual void BeginPlay() override;

public:
	
	TWeakObjectPtr<APlayerController> OwnerPlayerController;

	void ConstructInventoryWidget(const FWidgetControllerParams& WCParams);

	// Craft Stationlar  için 
	TWeakObjectPtr<UPlayerOpenInventoryWithCraftWidget> PlayerOpenInventoryWithCraftWidget;
	UPROPERTY(EditDefaultsOnly, Category = "AProps")
	TSubclassOf<UPlayerOpenInventoryWithCraftWidget> PlayerOpenInventoryWithCraftWidgetClass;

	// Craft olmayanlar için 
	TWeakObjectPtr<UPlayerOpenInventoryNoCraftWidget> PlayerOpenInventoryNoCraftWidget;
	UPROPERTY(EditDefaultsOnly, Category = "AProps")
	TSubclassOf<UPlayerOpenInventoryNoCraftWidget> PlayerOpenInventoryNoCraftWidgetClass;

	// Creatureler için
	TWeakObjectPtr<UPlayerOpenInventoryCreatureWidget> PlayerOpenInventoryCreatureWidget;
	UPROPERTY(EditDefaultsOnly, Category = "AProps")
	TSubclassOf<UPlayerOpenInventoryCreatureWidget> PlayerOpenInventoryCreatureWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UPlayerInventoryWidget> PlayerInventoryWidget;
	UPROPERTY(EditDefaultsOnly, Category = "AProps")
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass;

	UPlayerInventoryWidgetController* GetPlayerInventoryWidgetController(const FWidgetControllerParams& WCParams);
	UPROPERTY()
	TObjectPtr<UPlayerInventoryWidgetController> PlayerInventoryWidgetController;
	UPROPERTY(EditDefaultsOnly, Category = "AProps")
	TSubclassOf<UPlayerInventoryWidgetController> PlayerInventoryWidgetControllerClass;

	virtual void CloseAllWidgets() override;

	bool bPlayerInventoryOpen = false;
	void OpenPlayerInventory();
	void ClosePlayerInventory();

	void TogglePlayerInventory();

	
	
};
