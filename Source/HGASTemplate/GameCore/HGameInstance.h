// HANEDAN COMPANY

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HGASTEMPLATE_API UHGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FName PlayerStartTag = FName();

	UPROPERTY()
	FString LoadSlotName = FString();

	UPROPERTY()
	int32 LoadSlotIndex = 0;
	
};
