// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ScalableFloat.h"
#include "HGASTemplate/Interfaces/CombatInterface.h"

#include "HBaseCharacter.generated.h"

struct FGameplayTag;
class FOnDeathSignature;
class UDebuffNiagaraComponent;
class UNiagaraSystem;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;


UCLASS()
class HGASTEMPLATE_API AHBaseCharacter : public ACharacter, public ICombatInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

public:
	
	AHBaseCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void PostInitializeComponents() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Ability System Interface*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/** Ability System Interface*/
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	
	/** Combat Interface */
	virtual float GetXpReward() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual int32 I_GetLevel_Implementation() override;
	
	virtual FOnDeathSignature& GetOnDeathDelegate() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() override;
	virtual FOnDamageSignature& GetOnDamageSignature() override;
	/** Combat Interface */
	
	FOnASCRegistered OnAscRegistered;
	FOnDeathSignature OnDeathDelegate;
	FOnDamageSignature OnDamageDelegate;

	/**
	 * Codes related to ASC
	 */
	
	virtual void InitAbilityActorInfo();

	/** ASC ve AS nin initinden emin olduktan sonra çağırılan virtual fonksiyon */
	virtual void AbilitySystemInitialized(const UAbilitySystemComponent* ASC);

	/** Statların initialize edilme işlemi GE ler kullanılarak yapılıyor Bağımsızlar vital gibi olanlar instant effect
	 * bağımlı olanlar infinite effekt olarak uyguladık
	 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AProps")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AProps")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyGamePlayEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float Level) const;

	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();

	/** Karaktere eklenecek olan abilitylerin class arrayi */
	UPROPERTY(EditAnywhere,Category="AProps")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	/** Run time boyu çalışacak passive abilityler Event dinleyici ability olarak kullandık */
	UPROPERTY(EditAnywhere, Category = "AProps")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;

	/** XP - Level*/

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="AProps")
	FScalableFloat XpLevelCurveTable;

	// ------------------

	UPROPERTY(EditAnywhere,Category="AProps")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AProps")
	float BaseWalkSpeed = 600.f;
	
	UFUNCTION(NetMulticast,Reliable)
	virtual void Multicast_HandleDeath(const FVector& DeathImpulse);

	UPROPERTY(Replicated)
	bool bDead = false;

	UPROPERTY(EditDefaultsOnly,Category="AProps")
	TSubclassOf<UGameplayEffect> DeathEffect;

	UPROPERTY(EditDefaultsOnly,Category="AProps")
	TObjectPtr<USoundBase> DeathSound;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
	
};
