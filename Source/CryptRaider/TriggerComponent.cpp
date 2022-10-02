// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

#include "GrableActors.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	//UE_LOG(LogTemp,Display,TEXT("%f"),GetWorld()->TimeSeconds);

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	if(OverlappingActors.Num() > 0)
	{
		for (auto OverlappingActor : OverlappingActors)
		{
			const AGrableActors* ActiveGrableActor = reinterpret_cast<AGrableActors*>(OverlappingActor);
			if(ActiveGrableActor != nullptr && ActiveGrableActor->ActorHasTag(*AcceptableTagName)  && !ActiveGrableActor->GetGrableSituation())
			{
				return OverlappingActor;
			}
		}
	}
	return nullptr;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const AActor* AcceptableActor = GetAcceptableActor();
	if(AcceptableActor != nullptr)
	{
		UE_LOG(LogTemp,Display,TEXT("%s"),*(AcceptableActor->GetActorNameOrLabel()));
		//TODO Trigger
	}
}

