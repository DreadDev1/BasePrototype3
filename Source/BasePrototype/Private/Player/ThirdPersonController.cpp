// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ThirdPersonController.h"
#include "EnhancedInputComponent.h"
#include "Interaction/HighlightInterface.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUD/BaseHUD.h"


AThirdPersonController::AThirdPersonController()
{
	TraceLength = 500.f;
}

void AThirdPersonController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AThirdPersonController::Interact);
}

void AThirdPersonController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TraceForItem();
	TraceForCharacter();
}

bool AThirdPersonController::PerformLineTraceForItem(FHitResult& ItemHitResult)
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return true;
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2.f;
	FVector TraceStart;
	FVector Forward;
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return true;

	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	GetWorld()->LineTraceSingleByChannel(ItemHitResult, TraceStart, TraceEnd, ItemTraceChannel);
	return false;
}

void AThirdPersonController::TraceForItem()
{
	FHitResult ItemHitResult;
	if (PerformLineTraceForItem(ItemHitResult)) return;

	LastItem = ThisItem;
	ThisItem = ItemHitResult.GetActor();

	if (ThisItem == LastItem) return;

	// Highlight the item
	if (ThisItem) { ThisItem->HighlightActor(); }
	if (LastItem) { LastItem->UnHighlightActor(); }

	// Display the item's pickup message
	if (!ThisItem) { HidePickupMessage(); }
	if (ThisItem) { ShowPickupMessage(); }
}

bool AThirdPersonController::PerformCharacterTrace(FHitResult& CharacterHitResult)
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return true;
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2.f;
	FVector TraceStart;
	FVector Forward;
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return true;

	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	GetWorld()->LineTraceSingleByChannel(CharacterHitResult, TraceStart, TraceEnd, HighlightTraceChannel);
	return false;
}

void AThirdPersonController::TraceForCharacter()
{
	FHitResult CharacterHitResult;
	if (PerformCharacterTrace(CharacterHitResult)) return;

	LastCharacter = ThisCharacter;
	ThisCharacter = CharacterHitResult.GetActor();

	if (ThisCharacter == LastCharacter) return;
	if (ThisCharacter) { ThisCharacter->HighlightActor(); }
	if (LastCharacter) { LastCharacter->UnHighlightActor(); }
}

void AThirdPersonController::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("Primary Interact"))
}
