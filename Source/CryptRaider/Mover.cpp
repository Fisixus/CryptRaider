// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	StartingPos = GetOwner()->GetActorLocation();
	// ...
	
}

void UMover::Move(float DeltaTime) const
{
	const FVector CurrentLocation =  GetOwner() -> GetActorLocation();
	const FVector TargetPos = StartingPos + MoveOffset;
	const float Speed = FVector::Distance(TargetPos, StartingPos)/MoveTime;
	//const FVector NewPos = 	FMath::Lerp(CurrentLocation, TargetPos, ((DeltaTime*4)/0.5f)*((DeltaTime*4)/0.5f));
	const FVector NewPos = FMath::VInterpConstantTo(CurrentLocation, TargetPos, DeltaTime, Speed);
	UE_LOG(LogTemp,Display,TEXT("%v"), *(NewPos.ToString()));
	GetOwner()->SetActorLocation(NewPos);

}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(ShouldOpen)
		Move(DeltaTime);
	//FVector vec = GetOwner()->GetActorLocation();
	//FString s = vec.ToCompactString();
	//UE_LOG(LogTemp,Display,TEXT("%s"), *s);
	// ...
}
