// HANEDAN COMPANY

#pragma once

#include "CoreMinimal.h"
#include "HGASTemplate/Characters/HBaseCharacter.h"
#include "HGASTemplate/Interfaces/PlayerInterface.h"
#include "HCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API AHCharacter : public AHBaseCharacter, public IPlayerInterface
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	AHCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Players Interface */
	
	/** end Player Interface */

	/** Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual float GetXpReward() override;
	/** Combat Interface */
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	virtual void InitAbilityActorInfo() override;
	virtual void AbilitySystemInitialized(const UAbilitySystemComponent* ASC) override;

	/** Karakter yeniden doğunca yapılması gereken işlemler*/
	void ResetCharacterForRespawn();
	
	
};
