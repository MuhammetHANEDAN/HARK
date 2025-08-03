// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGASTemplate/Interfaces/InteractInterface.h"
#include "Chest.generated.h"

class UWidgetComponent;

UCLASS()
class HGASTEMPLATE_API AChest : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	
	AChest();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
	
	/**InteractInterface*/
	virtual void Interact_Implementation() override;
	virtual void InteractEnd_Implementation() override;
	virtual void FInteract_Implementation(AHPlayerController* HPlayerController) override;
	/**InteractInterface*/

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultRootComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> ShowMessageWidgetComponent;

	
	
};
