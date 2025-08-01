// HANEDAN COMPANY

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UHAttributeSet;
class UAbilitySystemComponent;
class UNiagaraSystem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnASCRegistered, UAbilitySystemComponent*)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, AActor*, DeadActor);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageSignature, float /*DamageAmount*/);

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SocketTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;
	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType) // BP Type koyduk bp de cast edebilelim diye
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HGASTEMPLATE_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	int32 GetPlayerLevel();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) // bp imp event yapınca virtual keywordu koymuyorsun
	void UpdateFacingTarget(const FVector& Target);

	/**
	 * Now, Blueprint Native event means that we don't have to mark this as virtual blueprint.
	 * Native event is going to automatically generate a virtual native version that exists in C plus plus
	 * that we can override here in C plus plus.
	 * And that's the version that has underscore implementation at the end of it.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	virtual void Die(const FVector& DeathImpulse) = 0;
	virtual FOnDeathSignature& GetOnDeathDelegate() = 0;
	virtual FOnDamageSignature& GetOnDamageSignature() = 0; 

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;
	
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() = 0;

	UFUNCTION(BlueprintNativeEvent)
	UHAttributeSet* I_GetHAS();

	virtual float GetXpReward() = 0;

	UFUNCTION(BlueprintNativeEvent)
	int32 I_GetLevel();
	
};
