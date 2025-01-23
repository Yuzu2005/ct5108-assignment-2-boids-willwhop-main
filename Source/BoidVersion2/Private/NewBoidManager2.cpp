// Fill out your copyright notice in the Description page of Project Settings.

#include "NewBoidManager2.h"
#include "NewBoids2.h"
#include "Walls.h"

// Sets default values
ANewBoidManager2::ANewBoidManager2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	transform = CreateDefaultSubobject<USceneComponent>("Root Scene Component");
	this -> SetRootComponent(transform);
}

// Called when the game starts or when spawned
void ANewBoidManager2::BeginPlay()
{
	Super::BeginPlay();
	//create boids equal to the amount given for spawn count
	for (int i = 0; i < spawncount; i++) {
		FVector SpawnLocation = (FMath::VRand() * FMath::RandRange(0.0f,spawnradius) ) + GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		//works like instantiating in unity
		ANewBoids2* boid = GetWorld()->SpawnActor<ANewBoids2>(SpawnLocation, SpawnRotation);
		boid->Manager = this;
		myboids.Add(boid);
	}
}

// Called every frame
void ANewBoidManager2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (ANewBoids2* boid : myboids) {
		boid->Update(DeltaTime);
	}
}

TArray<class ANewBoids2*> ANewBoidManager2::GetBoidNeighborhood(ANewBoids2* thisboid)
{
	TArray<class ANewBoids2*> returnboids;

	for (ANewBoids2* Boid : myboids) {
		if (Boid == thisboid || !Boid) {
			continue;
		}

		//if boid is a distance from another boid smaller than the neighborhood radius then add to rutturnboids.
		float adistance = (Boid->GetActorLocation() - thisboid->GetActorLocation()).Size();
		if (adistance < NeighborhoodRadius) {
			returnboids.Add(Boid);
		}
	}
	return returnboids;
}

FVector ANewBoidManager2::ClosestWall()
{
	FVector returnVal;
	//says for each boid it will check each wall and see if its in a specified range
	//if in range get the walls location and set max distance as a distance.
	float MaxDist = ObjectDistance;
	for (ANewBoids2* boid : myboids) {
		for (AWalls* wall : WallList) {
			float adistance = FVector::Distance(boid->GetActorLocation() , wall->GetActorLocation());
			if (adistance < MaxDist) {
				MaxDist = adistance;
				returnVal = wall->GetActorLocation();
			}
		}
	}
	return returnVal;
}




