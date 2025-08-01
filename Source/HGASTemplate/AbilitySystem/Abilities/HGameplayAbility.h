// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API UHGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	
	/**
	 * Burdaki tage göre oyunun başlangıcında karaktere gameplayabilityler veriliyor.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartUpInputTag;

	UFUNCTION(BlueprintPure)
	float GetValueFromScalableFloat(const FScalableFloat ScalableFloat, int32 Level) const;
	
	/**
	 * Önemli Sadece instanced olan GA larda kullan. GA başlatılmadan kullanma.
	 */
	UFUNCTION(BlueprintCallable)
	float GetAttributeValueByTag(const FGameplayTag AttributeTag) const;

protected:
	
	float GetManaCost(float InLevel = 1.f) const;
	float GetCooldown(float InLevel = 1.f) const;
	
};
