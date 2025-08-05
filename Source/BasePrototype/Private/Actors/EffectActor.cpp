// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "Game/AbilitySystem/Attributes/BaseAttributeSet.h"


// Sets default values
AEffectActor::AEffectActor()
{
	
	PrimaryActorTick.bCanEverTick = false;

	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UBaseAttributeSet* AuraAttributeSet = Cast<UBaseAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UBaseAttributeSet::StaticClass()));

		UBaseAttributeSet* MutableAuraAttributeSet = const_cast<UBaseAttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AEffectActor::EndOverlap);
}
