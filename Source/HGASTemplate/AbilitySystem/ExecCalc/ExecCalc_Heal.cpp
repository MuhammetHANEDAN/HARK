// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecCalc_Heal.h"

#include "HGASTemplate/AbilitySystem/HAttributeSet.h"
#include "HGASTemplate/GamePlayTags/HGameplayTags.h"
#include "HGASTemplate/Interfaces/HAbilitySystemInterface.h"

UExecCalc_Heal::UExecCalc_Heal()
{
	
}

void UExecCalc_Heal::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                            FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
	const FHGamePlayTags& Tags = FHGamePlayTags::Get();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Heali specden aldık
	float Heal = Spec.GetSetByCallerMagnitude(Tags.Attributes_AbilityPower, false);

	// Source asc den ap yi çekip specdeki healin üzerine ekledik

	if (IHAbilitySystemInterface* ic = Cast<IHAbilitySystemInterface>(SourceASC))
	{
		float Add = ic->I_GetAttributeValueByTag(Tags.Attributes_AbilityPower);
		Heal += Add;
	}
	
	const FGameplayModifierEvaluatedData HealData(UHAttributeSet::GetIncomingHealAttribute(), EGameplayModOp::Additive,Heal );
	OutExecutionOutput.AddOutputModifier(HealData);
}
