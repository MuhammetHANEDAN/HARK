
#include "HPlayerState.h"
#include "HGASTemplate/AbilitySystem/HAbilitySystemComponent.h"
#include "HGASTemplate/AbilitySystem/HAttributeSet.h"
#include "HGASTemplate/Inventory/Components/PlayerInventoryComponent.h"
#include "HGASTemplate/UI/WidgetControllers/HWidgetController.h"
#include "Net/UnrealNetwork.h"

AHPlayerState::AHPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UHAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UHAttributeSet>("AttributeSet");

	PlayerInventoryComponent = CreateDefaultSubobject<UPlayerInventoryComponent>("Player Inventory Comp");
	PlayerInventoryComponent->SetIsReplicated(true);
}

void AHPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHPlayerState,Level);
	DOREPLIFETIME(AHPlayerState, XP);
	DOREPLIFETIME(AHPlayerState, AttributePoints);
	DOREPLIFETIME(AHPlayerState, SpellPoints);
}

void AHPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerInventoryComponent->OwnerPlayerController = GetPlayerController();
}

UAbilitySystemComponent* AHPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AHPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AHPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level, true);
}

void AHPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AHPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level, false);
}

UPlayerInventoryComponent* AHPlayerState::GetPlayerInventoryComponent() 
{
	return PlayerInventoryComponent.Get();
}

void AHPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level, true);
}

void AHPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

void AHPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AHPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AHPlayerState::AddToAttributePoints(int32 InPoints)
{
	AttributePoints += InPoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AHPlayerState::AddToSpellPoints(int32 InPoints)
{
	SpellPoints += InPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AHPlayerState::ConstructPlayerInventoryWidget()
{
	FWidgetControllerParams Params;
	Params.AbilitySystemComponent = AbilitySystemComponent;
	Params.AttributeSet = AttributeSet;
	Params.PlayerState = this;
	Params.PlayerController = GetPlayerController();
	
	PlayerInventoryComponent->ConstructInventoryWidget(Params);
}