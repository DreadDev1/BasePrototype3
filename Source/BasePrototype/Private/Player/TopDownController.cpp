// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TopDownController.h"

#include "Interaction/HighlightInterface.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "BasePrototype/Public/UI/BaseUserWidget.h"

class UInv_ItemComponent;

void ATopDownController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ATopDownController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CursorTraceCharacter();
	CursorTraceItem();
}

void ATopDownController::CursorTraceCharacter()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(HighlightTraceChannel, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastCharacter = ThisCharacter;
	ThisCharacter = CursorHit.GetActor();

	if (ThisCharacter == LastCharacter) return;
	if (ThisCharacter) { ThisCharacter->HighlightActor(); }
	if (LastCharacter) { LastCharacter->UnHighlightActor(); }
}

void ATopDownController::CursorTraceItem()
{
	FHitResult CursorHitItem;
	GetHitResultUnderCursor(ItemTraceChannel, false, CursorHitItem);
	if (!CursorHitItem.bBlockingHit && LastItem == nullptr) return;
	
	LastItem = ThisItem;
	ThisItem = CursorHitItem.GetActor();

	if (ThisItem == LastItem) return;

	// Highlight the item
	if (ThisItem) { ThisItem->HighlightActor(); }
	if (LastItem) { LastItem->UnHighlightActor(); }

	// Display the item's pickup message
	if (!ThisItem) { HidePickupMessage(); }
	if (ThisItem) { ShowPickupMessage(); }
}
