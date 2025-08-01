// Fill out your copyright notice in the Description page of Project Settings.


#include "HProjectileAbility.h"

void UHProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHProjectileAbility::SpawnProjectile(const FVector& ProjectileSpawnLocation,
                                          const FRotator& ProjectileSpawnRotation)
{
	/*const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(ProjectileSpawnLocation);
	SpawnTransform.SetRotation(ProjectileSpawnRotation.Quaternion());
		
	AHProjectile* Projectile = GetWorld()->SpawnActorDeferred<AHProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetAvatarActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
	Projectile->ActorLevel = GetAbilityLevel();
		
	Projectile->FinishSpawning(SpawnTransform);*/
}

void UHProjectileAbility::SpawnProjectileHoming(AActor* HomingTargetActor, const FVector& SocketLocation)
{
	/*const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	if (HomingTargetActor == nullptr) return;

	FRotator Rotation = (HomingTargetActor->GetActorLocation() - SocketLocation).Rotation();
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
		
	AHProjectile* Projectile = GetWorld()->SpawnActorDeferred<AHProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetAvatarActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

	Projectile->ActorLevel = GetAbilityLevel();
	Projectile->NormalAttackSlowPercent = GetAttributeValueByTag(FHGamePlayTags::Get().Attributes_NormalAttackSlow);

	Projectile->DamageEffectParams.BaseDamage = GetAttributeValueByTag(FHGamePlayTags::Get().Attributes_AttackDamage);

	Projectile->ProjectileMovement->HomingTargetComponent = HomingTargetActor->GetRootComponent();
	Projectile->ProjectileMovement->HomingAccelerationMagnitude = HomingAcceleration;
	Projectile->ProjectileMovement->bIsHomingProjectile = true;

	Projectile->bIsHomingProjectile = true;
	Projectile->HomingTargetActor = HomingTargetActor;
		
	Projectile->FinishSpawning(SpawnTransform);*/
}
