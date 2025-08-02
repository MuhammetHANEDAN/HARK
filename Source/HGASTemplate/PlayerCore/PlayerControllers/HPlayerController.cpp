
#include "HPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HGASTemplate/AbilitySystem/HAbilitySystemComponent.h"
#include "HGASTemplate/Characters/HCharacter.h"
#include "HGASTemplate/GamePlayTags/HGameplayTags.h"
#include "HGASTemplate/Input/HInputComponent.h"
#include "HGASTemplate/UI/WidgetComponents/DamageTextWidgetComponent.h"


AHPlayerController::AHPlayerController()
{
	bReplicates = true;
}

void AHPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//CursorTrace();
	
}

void AHPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(HMappingContext); 

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(HMappingContext,0);
	}
	
/*	bShowMouseCursor = true;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);*/

	
}

void AHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UHInputComponent* HInputComponent = CastChecked<UHInputComponent>(InputComponent);

	HInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AHPlayerController::Move);

	HInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
	
}

void AHPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	
	if (GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
}

void AHPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FHGamePlayTags::Get().Player_Block_InputReleased))
	{
		return;
	}
	
	if(GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	
}

void AHPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FHGamePlayTags::Get().Player_Block_InputHeld))
	{
		return;
	}

	GetASC()->AbilityInputTagHeld(InputTag);
}

UHAbilitySystemComponent* AHPlayerController::GetASC() const
{
	if(HAbilitySystemComponent == nullptr)
	{
		UAbilitySystemComponent* DASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<AHCharacter>());
		return Cast<UHAbilitySystemComponent>(DASC);
	}
	return HAbilitySystemComponent;
}

void AHPlayerController::Move(const FInputActionValue& InputActionValue)
{
	/*if (GetASC() && GetASC()->HasMatchingGameplayTag(FHGamePlayTags::Get().Player_Block_InputPressed))
	{
		return;
	}*/
	
	const FVector2d InputActionVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0,Rotation.Yaw,0);

	const FVector FrontDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	ControlledPawn = GetPawn<APawn>();
	if(ControlledPawn)
	{
		ControlledPawn->AddMovementInput(FrontDirection, InputActionVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputActionVector.X);
	}
}

void AHPlayerController::CursorTrace()
{

	/*if (GetASC() && GetASC()->HasMatchingGameplayTag(FHGamePlayTags::Get().Player_Block_CursorTrace))
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->UnHighlightActor();
		LastActor = nullptr;
		ThisActor = nullptr;
		return;
	}
	
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	
	if(!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	if(LastActor != ThisActor)
	{
		if(LastActor) LastActor->UnHighlightActor();
		if(ThisActor) ThisActor->HighlightActor();
	}*/
}


void AHPlayerController::Client_ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextWidgetComponent* DamageText = NewObject<UDamageTextWidgetComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount,bBlockedHit,bCriticalHit);
	}
}
