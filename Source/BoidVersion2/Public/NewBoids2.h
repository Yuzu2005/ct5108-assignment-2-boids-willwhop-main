// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NewBoids2.generated.h"

UCLASS()
class BOIDVERSION2_API ANewBoids2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANewBoids2();

	FVector currentvelocity = FVector::ZeroVector;

	class ANewBoidManager2* Manager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector Seek(FVector position);
	FVector Flee(FVector position);
    FVector AvoidObject(FVector position);

	FVector Wander(float Radius, float Distance, float Jitter);
	FVector WanderDestination;

	FVector Seperation(TArray<ANewBoids2*> Neighbour);
	FVector Cohesion(TArray<ANewBoids2*> Neighbour);
	FVector Alignment(TArray<ANewBoids2*> Neighbour);
	
	UStaticMeshComponent* mesh;

	float speed = 1;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Update(float DeltaTime);
};
