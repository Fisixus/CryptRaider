// Fill out your copyright notice in the Description page of Project Settings.


#include "GrableActors.h"

// Sets default values
AGrableActors::AGrableActors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrableActors::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGrableActors::SetGrableSituation(bool newStatus)
{
	isGrabbed = newStatus;
}

bool AGrableActors::GetGrableSituation() const
{
	return isGrabbed;
}

// Called every frame
void AGrableActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



