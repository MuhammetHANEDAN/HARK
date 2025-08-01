// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HGASTemplate/HGASTemplate.h"
#include "HGASTemplate/AbilitySystem/HAbilitySystemComponent.h"
#include "HGASTemplate/GamePlayTags/HGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "WorldPartition/Cook/WorldPartitionCookPackage.h"


AHBaseCharacter::AHBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	const FHGamePlayTags& GameplayTags = FHGamePlayTags::Get();

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

}

void AHBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHBaseCharacter,bDead);
	
}

void AHBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AHBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHBaseCharacter::AbilitySystemInitialized(const UAbilitySystemComponent* ASC)
{
	
}

float AHBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnDamageDelegate.Broadcast(DamageTaken);
	return DamageTaken;
}

UAbilitySystemComponent* AHBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float AHBaseCharacter::GetXpReward()
{
	return XpLevelCurveTable.GetValueAtLevel(ICombatInterface::Execute_I_GetLevel(this));
}

void AHBaseCharacter::Die(const FVector& DeathImpulse)
{
	//Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true)); // Replicated Action
	
	Multicast_HandleDeath(DeathImpulse);
}

int32 AHBaseCharacter::I_GetLevel_Implementation()
{
	return 1;
}

FOnDeathSignature& AHBaseCharacter::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

void AHBaseCharacter::Multicast_HandleDeath_Implementation(const FVector& DeathImpulse)
{
	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetMesh()->AddImpulse(DeathImpulse, NAME_None, true);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	bDead = true;
	OnDeathDelegate.Broadcast(this);
}

FOnASCRegistered& AHBaseCharacter::GetOnASCRegisteredDelegate()
{
	return OnAscRegistered;
}

FVector AHBaseCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FHGamePlayTags& GameplayTags = FHGamePlayTags::Get();

	return FVector();
}

bool AHBaseCharacter::IsDead_Implementation() const
{
	return bDead;
}

FOnDamageSignature& AHBaseCharacter::GetOnDamageSignature()
{
	return OnDamageDelegate;
}

void AHBaseCharacter::InitAbilityActorInfo()
{
	
}

void AHBaseCharacter::ApplyGamePlayEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GamePlayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this); // important
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GamePlayEffectClass,Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent());
}

void AHBaseCharacter::InitializeDefaultAttributes() const
{
	ApplyGamePlayEffectToSelf(DefaultAttributes,1);
	ApplyGamePlayEffectToSelf(DefaultVitalAttributes,1);
}

void AHBaseCharacter::AddCharacterAbilities()
{
	UHAbilitySystemComponent* HASC = CastChecked<UHAbilitySystemComponent>(AbilitySystemComponent);
	if(!HasAuthority()) return;

	if(StartupAbilities.Num() == 0) return;

	HASC->AddCharacterAbilities(StartupAbilities);
	HASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}

void AHBaseCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (HasAuthority() == false) return;
	
	FHGamePlayTags FhGamePlayTags = FHGamePlayTags::Get();
	
	if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		IHAbilitySystemInterface::Execute_I_CancelAllActionAbilities(AbilitySystemComponent);
		
		AbilitySystemComponent->AddReplicatedLooseGameplayTag(FhGamePlayTags.Debuff_Knockback);
	}
	
	else
	{
		AbilitySystemComponent->RemoveReplicatedLooseGameplayTag(FhGamePlayTags.Debuff_Knockback);
	}
}




