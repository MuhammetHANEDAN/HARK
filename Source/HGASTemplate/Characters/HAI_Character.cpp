
#include "HAI_Character.h"

#include "AbilitySystemComponent.h"
#include "HGASTemplate/AbilitySystem/HAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HGASTemplate/HGASTemplate.h"
#include "HGASTemplate/AbilitySystem/HAbilitySystemComponent.h"



AHAI_Character::AHAI_Character()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UHAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UHAttributeSet>("AttributeSet");
	
	BaseWalkSpeed = 250.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void AHAI_Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	
}

void AHAI_Character::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
	InitAbilityActorInfo();
	
	if(HasAuthority())
	{
		//UHBlueprintFunctionLibrary::GiveStartupAbilities(this,AbilitySystemComponent, CharacterClass);
	}
	
	
}

void AHAI_Character::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UHAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet(); // Delegate bağlama

	//AbilitySystemComponent->RegisterGameplayTagEvent(FHGamePlayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AHAI_Character::StunTagChanged);

	if(HasAuthority())
	{
		InitializeDefaultAttributes();
	}

	OnAscRegistered.Broadcast(AbilitySystemComponent);
}

void AHAI_Character::InitializeDefaultAttributes() const
{
	
}

void AHAI_Character::AbilitySystemInitialized(const UAbilitySystemComponent* ASC)
{
	

	
	
}


void AHAI_Character::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AHAI_Character::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}

int32 AHAI_Character::GetPlayerLevel_Implementation()
{
	return Level;
}

void AHAI_Character::Die(const FVector& DeathImpulse)
{
	Super::Die(DeathImpulse);
}

float AHAI_Character::GetXpReward()
{
	return Super::GetXpReward();
}
