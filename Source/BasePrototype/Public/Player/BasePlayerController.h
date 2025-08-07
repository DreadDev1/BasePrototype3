// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UOverlayWidget;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UBaseUserWidget;
class IHighlightInterface;

UCLASS()
class BASEPROTOTYPE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category = "Base Prototype|TraceChannels")
	TEnumAsByte<ECollisionChannel> HighlightTraceChannel;
	UPROPERTY(EditDefaultsOnly, Category = "Base Prototype|TraceChannels")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;
	
	TScriptInterface<IHighlightInterface> ThisItem;
	TScriptInterface<IHighlightInterface> LastItem;
	// Character trace variables
	TScriptInterface<IHighlightInterface> ThisCharacter;
	TScriptInterface<IHighlightInterface> LastCharacter;

	UPROPERTY()
	TObjectPtr<UOverlayWidget> HUDWidget;

	void ShowPickupMessage();
	void HidePickupMessage();
	
private:

   	UPROPERTY(EditDefaultsOnly, Category = "Base Prototype|Inputs|Input Mapping Context")
   	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;
   	
   	void Move(const FInputActionValue& InputActionValue);
    UPROPERTY(EditDefaultsOnly, Category="Base Prototype|Inputs|Input Actions")
    TObjectPtr<UInputAction> MoveAction;
    
    void Look(const FInputActionValue& InputActionValue);
    UPROPERTY(EditDefaultsOnly, Category="Base Prototype|Inputs|Input Actions")
    TObjectPtr<UInputAction> LookAction;
	
};
