// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameplayAbility.h"

#include "HGASTemplate/AbilitySystem/HAttributeSet.h"


float UHGameplayAbility::GetValueFromScalableFloat(const FScalableFloat ScalableFloat, int32 Level) const
{
	return ScalableFloat.GetValueAtLevel(Level);
}

float UHGameplayAbility::GetAttributeValueByTag(const FGameplayTag AttributeTag) const
{
	if (GetAbilitySystemComponentFromActorInfo() == nullptr)
	{
		return 0.f;
	}
	
	if (const UHAttributeSet* AttributeSet = Cast<UHAttributeSet>(GetAbilitySystemComponentFromActorInfo()->GetAttributeSet(UHAttributeSet::StaticClass())))
	{
		for (auto& Element : AttributeSet->TagsToAttributes)
		{
			if (AttributeTag.MatchesTagExact(Element.Key))
			{
				return Element.Value().GetNumericValue(GetAbilitySystemComponentFromActorInfo()->GetAttributeSet(UHAttributeSet::StaticClass()));
			}
		}
	}
	return 0.f;
}

float UHGameplayAbility::GetManaCost(float InLevel) const
{
	float ManaCost = 0.f;
	if (const UGameplayEffect* CostEffect = GetCostGameplayEffect())
	{
		for (FGameplayModifierInfo Mod : CostEffect->Modifiers)
		{
			if (Mod.Attribute == UHAttributeSet::GetManaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				break;
			}
		}
	}
	return ManaCost;
}

float UHGameplayAbility::GetCooldown(float InLevel) const
{
	float Cooldown = 0.f;
	if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
	{
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
	}
	return Cooldown;
}