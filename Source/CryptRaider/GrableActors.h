// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrableActors.generated.h"

UENUM(BlueprintType)
enum EGrableObjects 
{
	Gargoyle = 0, 
	Statue = 1, 
};

UCLASS()
class CRYPTRAIDER_API AGrableActors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrableActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetGrableSituation(bool newStatus);
	bool GetGrableSituation() const;
private:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EGrableObjects> Type;
	UPROPERTY(EditAnywhere)
	bool isGrabbed = false;
};
