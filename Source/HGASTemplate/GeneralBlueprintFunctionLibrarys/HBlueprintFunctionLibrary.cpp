// Fill out your copyright notice in the Description page of Project Settings.


#include "HBlueprintFunctionLibrary.h"


#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Engine/OverlapResult.h"
#include "HGASTemplate/AbilitySystem/HAbilitySystemComponent.h"
#include "HGASTemplate/AbilitySystem/HAbilityTypes/HAbilityTypes.h"
#include "HGASTemplate/GameCore/GameModes/HGameMode.h"
#include "HGASTemplate/GamePlayTags/HGameplayTags.h"
#include "HGASTemplate/Interfaces/CombatInterface.h"
#include "HGASTemplate/PlayerCore/PlayerStates/HPlayerState.h"
#include "HGASTemplate/UI/HUDS/HHUD.h"
#include "HGASTemplate/UI/WidgetControllers/HWidgetController.h"
#include "Kismet/GameplayStatics.h"


bool UHBlueprintFunctionLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AHHUD*& OutHHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutHHUD = Cast<AHHUD>(PC->GetHUD());
		if (OutHHUD)
		{
			AHPlayerState* PS = PC->GetPlayerState<AHPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			OutWCParams.AttributeSet = AS;
			OutWCParams.AbilitySystemComponent = ASC;
			OutWCParams.PlayerState = PS;
			OutWCParams.PlayerController = PC;
			return true;
		}
	}
	return false;
}

float UHBlueprintFunctionLibrary::GetAttributeValueByTag(AActor* OwnerActor, const FGameplayTag AttributeTag)
{
	if (OwnerActor == nullptr) return 0.f;

	if (UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor))
	{
		UHAbilitySystemComponent* HASC = Cast<UHAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor));
		if (HASC)
		{
			return HASC->GetAttributeValueByTag(AttributeTag);
		}
		return 0;
	}

	return 0;
}

float UHBlueprintFunctionLibrary::GetValueFromScalableFloat(const FScalableFloat ScalableFloat, int32 Level)
{
	return ScalableFloat.GetValueAtLevel(Level);
}

bool UHBlueprintFunctionLibrary::IsEnemy(AActor* FirstActor, AActor* SecondActor)
{
	return true;
}

void UHBlueprintFunctionLibrary::SetIsRadialDamageEffectParam(FDamageEffectParams& DamageEffectParams, bool bIsRadial, float InnerRadius, float OuterRadius, FVector Origin)
{
	/*DamageEffectParams.bIsRadialDamage = bIsRadial;
	DamageEffectParams.RadialDamageInnerRadius = InnerRadius;
	DamageEffectParams.RadialDamageOuterRadius = OuterRadius;
	DamageEffectParams.RadialDamageOrigin = Origin;*/
}

void UHBlueprintFunctionLibrary::SetDeathImpulseDirection(FDamageEffectParams& DamageEffectParams, FVector ImpulseDirection, float Magnitude)
{
	//ImpulseDirection.Normalize();
	/*if (Magnitude == 0.f)
	{
		DamageEffectParams.DeathImpulse = ImpulseDirection * DamageEffectParams.DeathImpulseMagnitude;
	}*/
	/*else
	{
		DamageEffectParams.DeathImpulse = ImpulseDirection * Magnitude;
	}*/
}

void UHBlueprintFunctionLibrary::SetTargetEffectParamsASC(FDamageEffectParams& DamageEffectParams,
	UAbilitySystemComponent* InASC)
{
	DamageEffectParams.TargetAbilitySystemComponent = InASC;
}

bool UHBlueprintFunctionLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->IsBlockedHit();
	}
	return false;
}

bool UHBlueprintFunctionLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	/*if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->IsSuccessfulDebuff();
	}*/
	return false;
}

float UHBlueprintFunctionLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->GetDebuffDamage();
	}
	return 0.f;
}

float UHBlueprintFunctionLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->GetDebuffDuration();
	}
	return 0.f;
}

float UHBlueprintFunctionLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->GetDebuffFrequency();
	}
	return 0.f;
}

FGameplayTag UHBlueprintFunctionLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	/*if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if (HEffectContext->GetDamageType().IsValid())
		{
			return *HEffectContext->GetDamageType();
		}
	}*/
	return FGameplayTag();
}

FVector UHBlueprintFunctionLibrary::GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle)
{
	/*if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->GetDeathImpulse();
	}*/
	return FVector::ZeroVector;
}

FVector UHBlueprintFunctionLibrary::GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->GetKnockbackForce();
	}
	return FVector::ZeroVector;
}

bool UHBlueprintFunctionLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->IsCriticalHit();
	}
	return false;
}

bool UHBlueprintFunctionLibrary::IsRadialDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	/*if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->IsRadialDamage();
	}*/
	return false;
}

float UHBlueprintFunctionLibrary::GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& EffectContextHandle)
{
	/*if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->GetRadialDamageInnerRadius();
	}*/
	return 0.f;
}

float UHBlueprintFunctionLibrary::GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& EffectContextHandle)
{
	/*if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->GetRadialDamageOuterRadius();
	}*/
	return 0.f;
}

FVector UHBlueprintFunctionLibrary::GetRadialDamageOrigin(const FGameplayEffectContextHandle& EffectContextHandle)
{
	/*if (const FHGameplayEffectContext* HEffectContext = static_cast<const FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return HEffectContext->GetRadialDamageOrigin();
	}*/
	return FVector::ZeroVector;
}

void UHBlueprintFunctionLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UHBlueprintFunctionLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UHBlueprintFunctionLibrary::SetIsSuccessfulDebuff(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInSuccessfulDebuff)
{
	/*if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetIsSuccessfulDebuff(bInSuccessfulDebuff);
	}*/
}

void UHBlueprintFunctionLibrary::SetDebuffDamage(FGameplayEffectContextHandle& EffectContextHandle, float InDamage)
{
	if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetDebuffDamage(InDamage);
	}
}

void UHBlueprintFunctionLibrary::SetDebuffDuration(FGameplayEffectContextHandle& EffectContextHandle, float InDuration)
{
	if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetDebuffDuration(InDuration);
	}
}

void UHBlueprintFunctionLibrary::SetDebuffFrequency(FGameplayEffectContextHandle& EffectContextHandle, float InFrequency)
{
	if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetDebuffFrequency(InFrequency);
	}
}

void UHBlueprintFunctionLibrary::SetDamageType(FGameplayEffectContextHandle& EffectContextHandle,
	const FGameplayTag& InDamageType)
{
	/*if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		HEffectContext->SetDamageType(DamageType);
	}*/
}

void UHBlueprintFunctionLibrary::SetDeathImpulse(FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InImpulse)
{
	/*if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetDeathImpulse(InImpulse);
	}*/
}

void UHBlueprintFunctionLibrary::SetKnockbackForce(FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InForce)
{
	if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetKnockbackForce(InForce);
	}
}

void UHBlueprintFunctionLibrary::SetIsRadialDamage(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsRadialDamage)
{
	/*if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetIsRadialDamage(bInIsRadialDamage);
	}*/
}

void UHBlueprintFunctionLibrary::SetRadialDamageInnerRadius(FGameplayEffectContextHandle& EffectContextHandle,
	float InInnerRadius)
{
	/*if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetRadialDamageInnerRadius(InInnerRadius);
	}*/
}

void UHBlueprintFunctionLibrary::SetRadialDamageOuterRadius(FGameplayEffectContextHandle& EffectContextHandle,
	float InOuterRadius)
{
	/*if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetRadialDamageOuterRadius(InOuterRadius);
	}*/
}

void UHBlueprintFunctionLibrary::SetRadialDamageOrigin(FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InOrigin)
{
	/*if (FHGameplayEffectContext* HEffectContext = static_cast<FHGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		HEffectContext->SetRadialDamageOrigin(InOrigin);
	}*/
}

void UHBlueprintFunctionLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
                                                           TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,
                                                           const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(Overlap.GetActor());
			}
		}
	}
}

void UHBlueprintFunctionLibrary::GetClosestTargets(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin)
{
	if (Actors.Num() <= MaxTargets)
	{
		OutClosestTargets = Actors;
		return;
	}

	TArray<AActor*> ActorsToCheck = Actors;
	int32 NumTargetsFound = 0;

	while (NumTargetsFound < MaxTargets)
	{
		if (ActorsToCheck.Num() == 0) break;
		double ClosestDistance = TNumericLimits<double>::Max();
		AActor* ClosestActor;
		for (AActor* PotentialTarget : ActorsToCheck)
		{
			const double Distance = (PotentialTarget->GetActorLocation() - Origin).Length();
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = PotentialTarget;
			}
		}
		ActorsToCheck.Remove(ClosestActor);
		OutClosestTargets.AddUnique(ClosestActor);
		++NumTargetsFound;
	}
}

bool UHBlueprintFunctionLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bFriends = bBothArePlayers || bBothAreEnemies;
	return !bFriends;
}

TArray<FRotator> UHBlueprintFunctionLibrary::EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators)
{
	TArray<FRotator> Rotators;
	
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
	if (NumRotators > 1)
	{
		const float DeltaSpread = Spread / (NumRotators - 1);
		for (int32 i = 0; i < NumRotators; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			Rotators.Add(Direction.Rotation());
		}
	}
	else
	{
		Rotators.Add(Forward.Rotation());
	}
	return Rotators;
}

TArray<FVector> UHBlueprintFunctionLibrary::EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors)
{
	TArray<FVector> Vectors;
	
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
	if (NumVectors > 1)
	{
		const float DeltaSpread = Spread / (NumVectors - 1);
		for (int32 i = 0; i < NumVectors; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			Vectors.Add(Direction);
		}
	}
	else
	{
		Vectors.Add(Forward);
	}
	return Vectors;
}