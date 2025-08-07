// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/BaseHUD.h"

#include "Player/BasePlayerController.h"
#include "UI/BaseUserWidget.h"
#include "UI/WidgetControllers/BaseWidgetController.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"


UOverlayWidgetController* ABaseHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void ABaseHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
    
	OverlayWidget = CreateWidget<UBaseUserWidget>(GetWorld(), OverlayWidgetClass);
	checkf(OverlayWidget, TEXT("Failed to create OverlayWidget"));
    
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	checkf(WidgetController, TEXT("Failed to create WidgetController"));

	OverlayWidget->SetWidgetController(WidgetController);
	// Make sure to broadcast initial values if needed
    
	OverlayWidget->AddToViewport();
}