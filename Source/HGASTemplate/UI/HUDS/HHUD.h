
// HANEDAN COMPANY

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HHUD.generated.h"

class USpellMenuWidgetController;
class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UHUserWidget;
/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API AHHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:

	virtual void BeginPlay() override;


private:

	
	











	
	
};

