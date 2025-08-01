
// HANEDAN COMPANY

#include "HGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "HGASTemplate/GameCore/HGameInstance.h"
#include "Kismet/GameplayStatics.h"


AActor* AHGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	UHGameInstance* HGameInstance = Cast<UHGameInstance>(GetGameInstance());
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		AActor* SelectedActor = Actors[0];
		for (AActor* Actor : Actors)
		{
			if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
			{
				if (PlayerStart->PlayerStartTag == HGameInstance->PlayerStartTag)
				{
					SelectedActor = PlayerStart;
					break;
				}
			}
		}
		return SelectedActor;
	}
	return nullptr;
}

void AHGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

