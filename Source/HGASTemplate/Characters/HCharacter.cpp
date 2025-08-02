
#include "HCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HGASTemplate/AbilitySystem/HAbilitySystemComponent.h"
#include "HGASTemplate/AbilitySystem/HAttributeSet.h"
#include "HGASTemplate/GameCore/GameModes/HGameMode.h"
#include "HGASTemplate/GamePlayTags/HGameplayTags.h"
#include "HGASTemplate/PlayerCore/PlayerControllers/HPlayerController.h"
#include "HGASTemplate/PlayerCore/PlayerStates/HPlayerState.h"
#include "HGASTemplate/UI/HUDS/HHUD.h"
#include "Kismet/GameplayStatics.h"


void AHCharacter::BeginPlay()
{
	Super::BeginPlay();
}

AHCharacter::AHCharacter()
{

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,400,0);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
}

void AHCharacter::PossessedBy(AController* NewController) // Serverde çalışıyor sadece
{
	Super::PossessedBy(NewController);
	
	// init ability actor info for server
	InitAbilityActorInfo();
	//AddCharacterAbilities(); // Sadece serverde çağılıması gerektiği için, startup abilityleri ekliyoruz.
}

void AHCharacter::OnRep_PlayerState() // Clientte
{
	Super::OnRep_PlayerState();
	
	// init ability actor info for client
	InitAbilityActorInfo();
}

int32 AHCharacter::GetPlayerLevel_Implementation()
{
	const AHPlayerState* HPlayerState = GetPlayerState<AHPlayerState>();
	check(HPlayerState);
	return HPlayerState->GetPlayerLevel();
}

float AHCharacter::GetXpReward()
{
	return Super::GetXpReward();
}

void AHCharacter::InitAbilityActorInfo()
{
	AHPlayerState* HPlayerState = GetPlayerState<AHPlayerState>();
	check(HPlayerState);
	HPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(HPlayerState,this);
	AbilitySystemComponent = HPlayerState->GetAbilitySystemComponent();
	Cast<UHAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet(); // Delegate bağlama
	AttributeSet = HPlayerState->GetAttributeSet();
	OnAscRegistered.Broadcast(AbilitySystemComponent);

	//AbilitySystemComponent->RegisterGameplayTagEvent(FHGamePlayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AHCharacter::StunTagChanged);

	if(AHPlayerController* HPlayerController = Cast<AHPlayerController>(Controller))
	{
		if(AHHUD* HHUD = Cast<AHHUD>(HPlayerController->GetHUD()))
		{
			HHUD->InitOverlay(HPlayerController,HPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}

	//InitializeDefaultAttributes();
}

void AHCharacter::AbilitySystemInitialized(const UAbilitySystemComponent* ASC)
{
	Super::AbilitySystemInitialized(ASC);
	
}

void AHCharacter::ResetCharacterForRespawn()
{
	
}
