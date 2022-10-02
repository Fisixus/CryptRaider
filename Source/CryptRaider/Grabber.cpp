// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "GrableActors.h"
#include "TriggerComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	Owner = GetOwner();
	PhysicsHandle = Owner -> FindComponentByClass<UPhysicsHandleComponent>();
	// ...
	
}

auto UGrabber::FindTheTargetStatue(FHitResult& Hit, const FVector& Start, const FVector& End,
                                   const ECollisionChannel ColChannel) const -> bool
{

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return World->SweepSingleByChannel(Hit,
			Start, End,
			FQuat::Identity,
			ECC_GameTraceChannel2,
			Sphere);
}

void UGrabber::Grab()
{
	if(PhysicsHandle == nullptr) return;
	FHitResult Hit;
	FVector StartVec = GetComponentLocation();
	FVector EndVec = StartVec + GetForwardVector()*MaxRayDistance;
	//DrawDebugLine(World, StartVec, EndVec, FColor::Red);
	ECollisionChannel Channel = ECC_GameTraceChannel2;
	bool HasHit = FindTheTargetStatue(Hit,StartVec, EndVec, Channel);
	if(HasHit)
	{
		ActiveGrableActor = reinterpret_cast<AGrableActors*>(Hit.GetActor());
		ActiveGrableActor->SetGrableSituation(true);
		
		Hit.GetComponent()->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			Hit.GetComponent(),
			NAME_None,
			Hit.ImpactPoint,
			GetComponentRotation()
		);
		DrawDebugSphere(World, Hit.ImpactPoint, 10, 10, FColor::Green, false, 5);
		//UE_LOG(LogTemp,Display,TEXT("%s"),*(Hit.GetActor()->GetActorNameOrLabel()));
	}
}

void UGrabber::Release()
{
	if(PhysicsHandle == nullptr) return;
	const auto GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if(GrabbedComponent != nullptr)
	{
		PhysicsHandle->ReleaseComponent();
		ActiveGrableActor->SetGrableSituation(false);
		ActiveGrableActor = nullptr;
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(PhysicsHandle != nullptr && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		//UE_LOG(LogTemp,Display,TEXT("%f"),GetWorld()->TimeSeconds);
		
		PhysicsHandle->SetTargetLocationAndRotation
		(
			Owner->GetActorLocation() + Owner->GetActorForwardVector()*GrabRadius*1.5f + Owner->GetActorUpVector()*GrabRadius/2,
			GetComponentRotation()
		);
	}
}






