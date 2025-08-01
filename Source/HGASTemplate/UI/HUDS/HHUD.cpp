
#include "HHUD.h"




void AHHUD::BeginPlay()
{
	Super::BeginPlay();

	
}


void AHHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	/*
	checkf(OverlayWidgetClass,TEXT("OverlayWidgetClass uninitialized please fill out BP_HHUD"));
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass uninitialized please fill out BP_HHUD"));
	
	OverlayWidget = CreateWidget<UHUserWidget>(GetWorld(),OverlayWidgetClass);

	FWidgetControllerParams WidgetControllerParams (PC,PS,ASC,AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController); // Bu fonkun içinde bp de firelanan delegate WidgetControllerSet(); var
	WidgetController->BroadcastInitialValues(); // Widget Controller içindeki delegateler broadcaste başlıyor 
	
	OverlayWidget->AddToViewport();*/
}
