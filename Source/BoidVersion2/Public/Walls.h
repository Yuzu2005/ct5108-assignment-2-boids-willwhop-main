// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Walls.generated.h"

UCLASS()
class BOIDVERSION2_API AWalls : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWalls();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings");
	AActor* managerActor;

	class ANewBoidManager2* Manager;
	UStaticMeshComponent* mesh;
	USceneComponent* transform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
