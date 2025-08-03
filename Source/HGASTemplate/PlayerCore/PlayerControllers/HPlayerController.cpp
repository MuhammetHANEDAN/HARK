
#include "HPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HGASTemplate/AbilitySystem/HAbilitySystemComponent.h"
#include "HGASTemplate/Characters/HCharacter.h"
#include "HGASTemplate/GamePlayTags/HGameplayTags.h"
#include "HGASTemplate/Input/HInputComponent.h"
#include "HGASTemplate/Interfaces/InteractInterface.h"
#include "HGASTemplate/Inventory/Components/PlayerInventoryComponent.h"
#include "HGASTemplate/PlayerCore/PlayerStates/HPlayerState.h"
#include "HGASTemplate/UI/WidgetComponents/DamageTextWidgetComponent.h"
#include "Kismet/GameplayStatics.h"


AHPlayerController::AHPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AHPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bCanTraceInteractChannel())
	{
		TraceInteractChannel();
	}
	
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
	HInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&AHPlayerController::Look);

	HInputComponent->BindAction(TogglePlayerInventoryAction,ETriggerEvent::Started,this,&AHPlayerController::TogglePlayerInventory);
	HInputComponent->BindAction(ESCAction,ETriggerEvent::Started,this,&AHPlayerController::ESCPressed);

	//HInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
	
}

void AHPlayerController::OnPossess(APawn* InPawn) // Sadece serverda Fire 
{
	Super::OnPossess(InPawn);

	if (IsLocalController())
	{
		UHInputComponent* HInputComponent = CastChecked<UHInputComponent>(InputComponent);

		ACharacter* CH = CastChecked<ACharacter>(InPawn);
		HInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,CH,&ACharacter::Jump);
	}
	
}

void AHPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	if (IsLocalController())
	{
		UHInputComponent* HInputComponent = CastChecked<UHInputComponent>(InputComponent);

		ACharacter* CH = CastChecked<ACharacter>(GetPawn());
		HInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,CH,&ACharacter::Jump);
	}
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

void AHPlayerController::TogglePlayerInventory()
{
	if (GetPlayerInventoryComponent())
	{
		GetPlayerInventoryComponent()->TogglePlayerInventory();
	}
}

void AHPlayerController::ESCPressed()
{
	if (GetPlayerInventoryComponent())
	{
		GetPlayerInventoryComponent()->CloseAllWidgets();
	}
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

void AHPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
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

bool AHPlayerController::bCanTraceInteractChannel()
{
	if (IsValid(GetPawn()) && IsLocalController()) return true;
	return false;
}

void AHPlayerController::TraceInteractChannel()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return;
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2.f;
	FVector TraceStart;
	FVector Forward;
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;

	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, InteractTraceChannel);
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, -1, 0, 1.f);

	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();

	if (ThisActor == LastActor) return;

	if (ThisActor.IsValid())
	{
		if (ThisActor->Implements<UInteractInterface>())
		{
			IInteractInterface::Execute_Interact(ThisActor.Get());
		}
	}

	if (LastActor.IsValid())
	{
		if (LastActor->Implements<UInteractInterface>())
		{
			IInteractInterface::Execute_InteractEnd(LastActor.Get());
		}
	}
}

UPlayerInventoryComponent* AHPlayerController::GetPlayerInventoryComponent() 
{
	if (!PlayerInventoryComponent.IsValid())
	{
		AHPlayerState* PS = GetPlayerState<AHPlayerState>();
		check(PS);
		PlayerInventoryComponent = PS->GetPlayerInventoryComponent();
		return PlayerInventoryComponent.Get();
	}
	return PlayerInventoryComponent.Get();
}

