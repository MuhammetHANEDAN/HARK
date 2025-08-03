
// HANEDAN COMPANY

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "HGASTemplate/Interfaces/AI_Interface.h"
#include "HPlayerController.generated.h"


class UPlayerInventoryComponent;
class UDamageTextWidgetComponent;
class UData_InputConfig;
class UNiagaraSystem;
class USplineComponent;
class UHAbilitySystemComponent;
class UHInputConfig;
class UHInputComponent;
class IEnemyInterface;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API AHPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AHPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	/** Damage Indicator Works*/
	UFUNCTION(Client, Reliable)
	void Client_ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit);
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextWidgetComponent> DamageTextComponentClass;

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:

	UPROPERTY(EditAnywhere,Category="AProps")
	TObjectPtr<UInputMappingContext> HMappingContext;

	UPROPERTY(EditAnywhere,Category="AProps")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere,Category="AProps")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere,Category="AProps")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere,Category="AProps")
	TObjectPtr<UInputAction> TogglePlayerInventoryAction;
	void TogglePlayerInventory();

	UPROPERTY(EditAnywhere,Category="AProps")
	TObjectPtr<UInputAction> ESCAction;
	void ESCPressed();
	
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& Value);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly,Category="AProps")
	TObjectPtr<UData_InputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UHAbilitySystemComponent> HAbilitySystemComponent;

	UHAbilitySystemComponent* GetASC() const;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnRep_Pawn() override;

	bool bCanTraceInteractChannel();
	void TraceInteractChannel();
	
	TWeakObjectPtr<AActor>LastActor;
	TWeakObjectPtr<AActor>ThisActor;

	UPROPERTY(EditDefaultsOnly, Category = "AProps")
	double TraceLength = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "AProps")
	TEnumAsByte<ECollisionChannel> InteractTraceChannel;
	
	UPROPERTY()
	APawn* ControlledPawn; // biz ekledik

	/**
	 * Inventory Releated
	 */

	TWeakObjectPtr<UPlayerInventoryComponent> PlayerInventoryComponent;

	UPlayerInventoryComponent* GetPlayerInventoryComponent() ;


	//---------------------- ?
	
};

