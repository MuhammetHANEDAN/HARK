// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "HAbilitySystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UHAbilitySystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HGASTEMPLATE_API IHAbilitySystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
public:
	
	virtual float I_GetAttributeValueByTag (const FGameplayTag& AttributeTag) = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void I_CancelAllActionAbilities();
};

