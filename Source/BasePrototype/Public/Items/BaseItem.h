// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/HighlightInterface.h"
#include "BaseItem.generated.h"

UCLASS()
class BASEPROTOTYPE_API ABaseItem : public AActor, public IHighlightInterface
{
	GENERATED_BODY()

public:
	ABaseItem();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Base Prototype|Items|Mesh")
	UStaticMeshComponent* ItemMesh;
};
