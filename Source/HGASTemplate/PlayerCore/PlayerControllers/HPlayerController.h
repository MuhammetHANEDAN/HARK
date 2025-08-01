
// HANEDAN COMPANY

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "HGASTemplate/Interfaces/AI_Interface.h"
#include "HPlayerController.generated.h"


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

private:

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> HMappingContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> ShiftAction;
	void ShiftPressed() {bShiftKeyDown = true;}
	void ShiftReleased() {bShiftKeyDown = false;}
	bool bShiftKeyDown = false;
	
	void Move(const FInputActionValue& InputActionValue);

	UPROPERTY()
	APawn* ControlledPawn; // biz ekledik

	void CursorTrace();
	FHitResult CursorHit;


	TScriptInterface<IAI_Interface> LastActor;
	TScriptInterface<IAI_Interface> ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UData_InputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UHAbilitySystemComponent> HAbilitySystemComponent;

	UHAbilitySystemComponent* GetASC() const;

	
	
};

