// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HGameplayAbility.h"
#include "HProjectileAbility.generated.h"

class AHProjectile;
/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API UHProjectileAbility : public UHGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileSpawnLocation, const FRotator& ProjectileSpawnRotation);

	UFUNCTION(BlueprintCallable, Category = "AProps")
	void SpawnProjectileHoming(AActor* HomingTargetActor,const FVector& SocketLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AHProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 1;

	UPROPERTY(EditDefaultsOnly, Category= "AProps")
	float HomingAcceleration = 3200.f;
};
