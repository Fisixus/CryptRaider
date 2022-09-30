// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UENUM(BlueprintType)
enum EGrableObjects 
{
	Gargoyle = 0, 
	Something = 1, 
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void Grab();
	UFUNCTION(BlueprintCallable)
	void Release();
	
private:
	UPROPERTY(EditAnywhere)
	float MaxRayDistance = 400;
	UPROPERTY(EditAnywhere)
    float GrabRadius = 100;

	UWorld* World;
	AActor* Owner;
	UPhysicsHandleComponent* PhysicsHandle;
	bool FindTheTargetStatue(FHitResult& Hit, const FVector& Start, const FVector& End,
	                         const ECollisionChannel ColChannel) const;
};
