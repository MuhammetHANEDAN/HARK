
#pragma once

#include "CoreMinimal.h"
#include "HBaseCharacter.h"
#include "HGASTemplate/Interfaces/AI_Interface.h"
#include "HAI_Character.generated.h"


class AHAIController;
class UBehaviorTree;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API AHAI_Character : public AHBaseCharacter, public IAI_Interface
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	AHAI_Character();
	virtual void PossessedBy(AController* NewController) override;

	/** ai interface*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** ai interface*/

	/** Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual float GetXpReward() override;
	/** Combat Interface */
	
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	virtual void AbilitySystemInitialized(const UAbilitySystemComponent* ASC) override;
	
	/**
	 * Replicated yapmadık çünkü zaten sadece serverde hesaplamalar yapılacak.
	 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AProps")
	int32 Level = 1;

	/**
	 * AI works
	 */

	/*UPROPERTY(EditAnywhere,Category="Aprops")
	TObjectPtr<UBehaviorTree> BehaviorTree;*/

	/*UPROPERTY()
	TObjectPtr<AHAIController> HAIController;*/

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite)
	TWeakObjectPtr<AActor> TargetActor;

	UPROPERTY(EditDefaultsOnly,Category="AProps|AI")
	float ChaseDistance = 1000.f;

	UPROPERTY(EditDefaultsOnly,Category="AProps|AI")
	float AttackTetherDistance = 30.f;

	UPROPERTY(EditDefaultsOnly,Category="AProps|AI")
	float DetectEnemyRange = 800.f;
	
	
	
};
