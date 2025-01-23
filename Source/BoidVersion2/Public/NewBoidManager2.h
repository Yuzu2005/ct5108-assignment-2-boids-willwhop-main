// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NewBoidManager2.generated.h"

UCLASS()
class BOIDVERSION2_API ANewBoidManager2 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANewBoidManager2();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config, Category = "Settings");
	int spawncount = 30;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config, Category = "Settings");
	float spawnradius = 500.f;
	//added BlueprintReadWrite so they could be set used in blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "Settings");
	float NeighborhoodRadius = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "Settings");
	float SeperationTime = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "Settings");
	float CohesionTime = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "Settings");
	float Alignment = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "Settings");
	int ObjectDistance = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "Settings");
	float SpeedForBoid = 5.f;

	USceneComponent* transform;

	TArray<class ANewBoids2*> myboids;

	TArray<class AWalls*> WallList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<class ANewBoids2*> GetBoidNeighborhood(class ANewBoids2* thisboid);

	FVector ClosestWall();
};
