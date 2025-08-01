// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HGASTemplate/Interfaces/HAbilitySystemInterface.h"
#include "HAbilitySystemComponent.generated.h"


/**
 * MarkAbilitySpecDirty() fonksiyonunu GA ye tag ekleyip çıkardığın zaman yada üstünde başka değişiklikler
 * yaptığında kullan
 */
UCLASS()
class HGASTEMPLATE_API UHAbilitySystemComponent : public UAbilitySystemComponent, public IHAbilitySystemInterface
{
	GENERATED_BODY()

	public:

	void AbilityActorInfoSet();

	/** HAbilitSystemInterface */
	virtual float I_GetAttributeValueByTag(const FGameplayTag& AttributeTag) override;
	virtual void I_CancelAllActionAbilities_Implementation() override;
	/** HAbilitSystemInterface */
	
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
	
	/**
	 *Giveability() fonku ile abilityi serverde ASC ye verince aşağıdaki rep notify clientlerde firelanıyor
	 * Fired activatable abilities replicating.
	 */
	virtual void OnRep_ActivateAbilities() override;


	
	
	float GetAttributeValueByTag(const FGameplayTag AttributeTag) const;
	void CancelAllActionAbilities();
	
};
