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
			const AGrableActors* ActiveGrableActor = dynamic_cast<AGrableActors*>(OverlappingActor);
			if(ActiveGrableActor != nullptr && ActiveGrableActor->ActorHasTag(*AcceptableTagName)  && !ActiveGrableActor->GetGrableSituation())
			{
				return OverlappingActor;
			}
		}
	}
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* AcceptableActor = GetAcceptableActor();
	if(Mover != nullptr && AcceptableActor != nullptr)
	{
		//const auto SceneComp = AcceptableActor->GetRootComponent();
		auto SubComponents = AcceptableActor -> GetComponents();
		for (auto SubComponent : SubComponents)
		{
			//SubComponent->DestroyPhysicsState();
			UPrimitiveComponent* PrimitiveComponent =  Cast<UPrimitiveComponent>(SubComponent);
			if(PrimitiveComponent != nullptr)
			{
				PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
				//PrimitiveComponent->SetSimulatePhysics(false);
				//UE_LOG(LogTemp,Display,TEXT("%s"),*(AcceptableActor->GetActorNameOrLabel()));

			}
		}
		AcceptableActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->OpenSecretDoor(nullptr);
		Mover = nullptr;
		//AcceptableActor = nullptr;
		// 	//TODO Trigger Animation first
		
		// if(PrimitiveComponent != nullptr)
		// {
		// 	UE_LOG(LogTemp,Display,TEXT("%s"),*(AcceptableActor->GetActorNameOrLabel()));
		// 	PrimitiveComponent->SetSimulatePhysics(false);
		// 	PrimitiveComponent -> AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		// 	Mover->OpenSecretDoor();
		// 	AcceptableActor = nullptr;
		// }
		// else
		// {
		// 	UE_LOG(LogTemp,Display,TEXT("NOPEE"));
		//
		// }
	}
}



