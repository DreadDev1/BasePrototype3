// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/BaseHUD.h"

#include "Player/BasePlayerController.h"
#include "UI/BaseUserWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	if (Widget)
	{
		Widget->AddToViewport();
		// Cast to your player controller and set the widget reference
		if (ABasePlayerController* PC = Cast<ABasePlayerController>(GetOwningPlayerController()))
		{
			PC->SetHUDWidget(Cast<UBaseUserWidget>(Widget));
		}
	}

}
