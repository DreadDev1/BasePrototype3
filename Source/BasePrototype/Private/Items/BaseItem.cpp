// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"

#include "BasePrototype/BasePrototype.h"


// Sets default values
ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
}

void ABaseItem::HighlightActor()
{
	ItemMesh->SetRenderCustomDepth(true);
	ItemMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ABaseItem::UnHighlightActor()
{
	ItemMesh->SetRenderCustomDepth(false);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

