// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "ThirdPersonController.generated.h"

class ABaseCharacter;

UCLASS()
class BASEPROTOTYPE_API AThirdPersonController : public ABasePlayerController
{
	GENERATED_BODY()
	AThirdPersonController();

public:

protected:
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	bool PerformLineTraceForItem(FHitResult& ItemHitResult);
	void TraceForItem();
	bool PerformCharacterTrace(FHitResult& CharacterHitResult);
	void TraceForCharacter();
	UPROPERTY(EditDefaultsOnly, Category = "Base Prototype|TraceChannels")
	double TraceLength;

private:

	void Interact();
	UPROPERTY(EditDefaultsOnly, Category = "Base Prototype|Inputs|Input Actions")
	TObjectPtr<UInputAction> InteractAction;
};
