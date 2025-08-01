// Fill out your copyright notice in the Description page of Project Settings.

#include "HAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "HAttributeSet.h"
#include "Abilities/HGameplayAbility.h"
#include "HGASTemplate/GamePlayTags/HGameplayTags.h"

void UHAbilitySystemComponent::AbilityActorInfoSet()
{
	if (GetAvatarActor()->HasAuthority())
	{
		RegisterGameplayTagEvent(FHGamePlayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddWeakLambda(this,
		[this](const FGameplayTag& CallBackTag, int32 NewCount)
		{
			if (NewCount > 0)
			{
				CancelAllActionAbilities();
			}
		});

		RegisterGameplayTagEvent(FHGamePlayTags::Get().Debuff_Knockback, EGameplayTagEventType::NewOrRemoved).AddWeakLambda(this,
			[this](const FGameplayTag& CallBackTag, int32 NewCount)
			{
				if (NewCount > 0)
				{
					CancelAllActionAbilities();
				}
			});
	}
}

float UHAbilitySystemComponent::I_GetAttributeValueByTag(const FGameplayTag& AttributeTag)
{
	return GetAttributeValueByTag(AttributeTag);
}

void UHAbilitySystemComponent::I_CancelAllActionAbilities_Implementation()
{
	CancelAllActionAbilities();
}

void UHAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for(auto& AbilityClass: StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1); // Ability classla AbilitySpec oluşturuldu

		if(const UHGameplayAbility* HAbility = Cast<UHGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(HAbility->StartUpInputTag);
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(FHGamePlayTags::Get().Abilities_Status_Equipped);
			GiveAbility(AbilitySpec); // Ability, ASC ye eklenmiş oluyor 
		}
	}
	
}

void UHAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupPassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UHAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	FScopedAbilityListLock ActiveScopeLoc(*this);
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag)  && AbilitySpec.IsActive())
		{
			//AbilitySpecInputPressed(AbilitySpec);
			//InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());

			TArray<UGameplayAbility*> Instances = AbilitySpec.GetAbilityInstances();
			const FGameplayAbilityActivationInfo& ActivationInfo = Instances.Last()->GetCurrentActivationInfoRef();
			FPredictionKey OriginalPredictionKey = ActivationInfo.GetActivationPredictionKey();
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, OriginalPredictionKey);
		}
	}
}

void UHAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;

	FScopedAbilityListLock ActiveScopeLoc(*this);

	for(auto& AbilitySpec : GetActivatableAbilities()) // GetActivatableAbilities() ->  Anladığımıza göre GiveAbility(AbilitySpec); bununla ekledik activatable abilitylere
	{
		if(AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec); // abilitye presslendiğinin bilgisini iletiyoruz
			if(!AbilitySpec.IsActive()) // Ability aktif değilse devam et
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UHAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;

	FScopedAbilityListLock ActiveScopeLoc(*this);

	for(auto& AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			//AbilitySpecInputReleased(AbilitySpec); // abilitye released olduğu bilgisini iletiyoruz
			// belki ability inputun release olması durumunda abilitye özel bir şeyler yaptırabilirz
			//InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());

			

			TArray<UGameplayAbility*> Instances = AbilitySpec.GetAbilityInstances();
			const FGameplayAbilityActivationInfo& ActivationInfo = Instances.Last()->GetCurrentActivationInfoRef();
			FPredictionKey OriginalPredictionKey = ActivationInfo.GetActivationPredictionKey();
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, OriginalPredictionKey);
		}
	}
}

FGameplayTag UHAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability)
	{
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UHAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (FGameplayTag Tag : AbilitySpec.GetDynamicSpecSourceTags())
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag"))))
		{
			return Tag;
		}
	}
	return FGameplayTag();
}

FGameplayTag UHAbilitySystemComponent::GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (FGameplayTag StatusTag : AbilitySpec.GetDynamicSpecSourceTags())
	{
		if (StatusTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities.Status"))))
		{
			return StatusTag;
		}
	}
	return FGameplayTag();
}

void UHAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
}

FGameplayAbilitySpec* UHAbilitySystemComponent::GetSpecFromAbilityTag(const FGameplayTag& AbilityTag)
{
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(AbilityTag))
			{
				return &AbilitySpec;
			}
		}
	}
	return nullptr;
}

float UHAbilitySystemComponent::GetAttributeValueByTag(const FGameplayTag AttributeTag) const
{
	if (const UHAttributeSet* AttributeSet = Cast<UHAttributeSet>(GetAttributeSet(UHAttributeSet::StaticClass())))
	{
		for (auto& Element : AttributeSet->TagsToAttributes)
		{
			if (AttributeTag.MatchesTagExact(Element.Key))
			{
				return Element.Value().GetNumericValue(GetAttributeSet(UHAttributeSet::StaticClass()));
			}
		}
	}
	return 0.f;
}

void UHAbilitySystemComponent::CancelAllActionAbilities()
{
	if (GetActivatableAbilities().Num() == 0) return;
	
	FScopedAbilityListLock ActiveScopeLoc(*this);

	FHGamePlayTags Tags = FHGamePlayTags::Get();
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.IsActive() && AbilitySpec.Ability->AbilityTags.HasTagExact(Tags.AbilityTypes_Action))
		{
			CancelAbility(AbilitySpec.Ability);
		}
	}
}
