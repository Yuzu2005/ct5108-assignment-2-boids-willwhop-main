// Fill out your copyright notice in the Description page of Project Settings.


#include "Walls.h"
#include "NewBoidManager2.h"
#include "NewBoids2.h"

// Sets default values
AWalls::AWalls()
{
	transform = CreateDefaultSubobject<USceneComponent>("Root Scene Component");
	this->SetRootComponent(transform);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	UStaticMesh* Boxmesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	mesh->SetStaticMesh(Boxmesh);
	this->SetRootComponent(mesh);
}

// Called when the game starts or when spawned
void AWalls::BeginPlay()
{
	Super::BeginPlay();
	// casts to manager and adds the wall t the wall list in it
	Manager = Cast<ANewBoidManager2>(managerActor);
		Manager->WallList.Add(this);
		FVector size = FVector(10, 5, 10);
		
}

// Called every frame
void AWalls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

