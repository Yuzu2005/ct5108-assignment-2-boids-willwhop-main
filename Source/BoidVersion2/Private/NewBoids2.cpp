// Fill out your copyright notice in the Description page of Project Settings.


#include "NewBoids2.h"
#include "NewBoidManager2.h"
#include "Walls.h"

// Sets default values
ANewBoids2::ANewBoids2()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	UStaticMesh* spheremesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")).Object;
	mesh->SetStaticMesh(spheremesh);
	this->SetRootComponent(mesh);
}

// Called when the game starts or when spawned
void ANewBoids2::BeginPlay()
{
	Super::BeginPlay();
}

FVector ANewBoids2::Seek(FVector position)
{
	FVector NewVelocity = position - GetActorLocation();
	NewVelocity.Normalize();
	return NewVelocity;
}

FVector ANewBoids2::Flee(FVector position)
{
	FVector NewVelocity = GetActorLocation() - position;
	NewVelocity.Normalize();
	return NewVelocity;
}

FVector ANewBoids2::AvoidObject(FVector position)
{
	FVector NewVelocity = GetActorLocation() - position;
	NewVelocity.Normalize();
	return NewVelocity;
}

FVector ANewBoids2::Wander(float Radius, float Distance, float Jitter)
{
	FVector MyLocation = GetActorLocation();
	if (FVector::Dist(MyLocation, WanderDestination) < 100.0f) {
		//get new destination in front of boid
		FVector ProjectedPos = MyLocation + (GetActorForwardVector() * Distance);
		WanderDestination = ProjectedPos + (FMath::VRand() * FMath::RandRange(0.0f, Jitter));
	}
	//continue going to destination
	FVector JitterDestination = Seek(WanderDestination) + (FMath::VRand() * FMath::RandRange(0.0f, Jitter));
	return JitterDestination;
}

FVector ANewBoids2::Seperation(TArray<ANewBoids2*> Neighbour)
{
	//if neighbor amount is zero return vector as zero vector
	if (Neighbour.Num() == 0) return FVector::ZeroVector;
	FVector Avgflee;
	for (ANewBoids2* Boid : Neighbour) {
		//fort each boid make inverse val 1 divided by the distance of boid location and this location
		float InverseVal = 1 / FVector::Dist(Boid->GetActorLocation(), GetActorLocation());
		Avgflee += Flee(Boid->GetActorLocation()) * InverseVal;
	}
	Avgflee.Normalize();
	return Avgflee;
}

FVector ANewBoids2::Cohesion(TArray<ANewBoids2*> Neighbour)
{
	if (Neighbour.Num() == 0) return FVector::ZeroVector;
	FVector AvgLocation;
	float InverseVal = 1 / Neighbour.Num();
	for (ANewBoids2* Boid : Neighbour) {
		AvgLocation += Boid->GetActorLocation() * InverseVal;
	}
	//avgLocation is divided buy neighbor amount
	AvgLocation /= Neighbour.Num();
	return Seek(AvgLocation);
}

FVector ANewBoids2::Alignment(TArray<ANewBoids2*> Neighbour)
{
	if (Neighbour.Num() == 0) return FVector::ZeroVector;
	FVector NewVelocity;
	for (ANewBoids2* Boid : Neighbour) {
		NewVelocity += Boid->currentvelocity;
	}
	NewVelocity /= Neighbour.Num();
	NewVelocity.Normalize();
	return NewVelocity;
}

// Called every frame
void ANewBoids2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANewBoids2::Update(float DeltaTime)
{
	speed = Manager->SpeedForBoid;
	FVector Targetvelocity = FVector::ZeroVector;
	//add velocity
	FVector size;
	for (AWalls* wall : Manager->WallList) {
		size = wall->GetActorScale3D();
	}
	TArray<ANewBoids2*> closestBoidsPos = Manager->GetBoidNeighborhood(this);
	FVector closestObjectPos = Manager->ClosestWall();
	//adding steering behaviours
	    Targetvelocity += AvoidObject(closestObjectPos) * Manager->ObjectDistance;
		Targetvelocity += Seperation(closestBoidsPos) * Manager->SeperationTime;
		Targetvelocity += Cohesion(closestBoidsPos) * Manager->CohesionTime;
		Targetvelocity += Alignment(closestBoidsPos) * Manager->Alignment;

		Targetvelocity.Normalize();
		//if velocity length is less than one then boid should do the wandering function
		if (Targetvelocity.Size() < 1.0f) {
			Targetvelocity += Wander(100.0f, 200.0f, 50.0f);
			Targetvelocity.Normalize();
		}
		
	//apply force
	FVector newforce = Targetvelocity - currentvelocity;
	currentvelocity += newforce * DeltaTime;

	FVector location = GetActorLocation();
	location += (currentvelocity * speed * DeltaTime);

	SetActorLocation(location);

	
}

