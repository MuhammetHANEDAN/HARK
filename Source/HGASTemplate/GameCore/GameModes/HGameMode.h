// HANEDAN COMPANY

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HGameMode.generated.h"

class ULoadScreenSaveGame;
class USaveGame;
class UMVVM_LoadSlot;
class UAbilityInfo;
class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API AHGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

protected:
	
	virtual void BeginPlay() override;
	
};
