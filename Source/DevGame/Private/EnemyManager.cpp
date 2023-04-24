// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EngineUtils.h"
#include "SlugEnemy.h"

// Sets default values
AEnemyManager::AEnemyManager() :
	AccumulatedDeltaTime(0.0f), EnemySpawnTimeSeconds(3.0f),
	MaxNumberOfEnemies(5), ReferencePlane(0),
	EnemyClass(ASlugEnemy::StaticClass())
	
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int AEnemyManager::GetNumberOfEnemies() const
{
	int LivingEnemies = 0;
	for(TActorIterator<AActor> ActorItr(GetWorld(), EnemyClass); ActorItr; ++ActorItr)
	{
		LivingEnemies++;
	}
	return LivingEnemies;
}

FVector AEnemyManager::GetRandomLocationFromReferencePlane() const
{
	FVector RandomLocation;
	FVector Origin;
	FVector BoundsExtend;

	ReferencePlane->GetActorBounds(false, Origin, BoundsExtend);

	//Generate a random location within the bounding box.
	RandomLocation = FMath::RandPointInBox(FBox::BuildAABB(Origin, BoundsExtend));

	return RandomLocation;
}


void AEnemyManager::SpawnEnemy()
{
	FVector EnemySpawnLocation = GetRandomLocationFromReferencePlane();
	GetWorld()->SpawnActor(EnemyClass, &EnemySpawnLocation);
	
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
	/*const FString EnemySpawnPlaneString = FString(TEXT("EnemySpawnPlane"));

	//Search the EnemySpawnPlane in the world 
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if(EnemySpawnPlaneString.Equals(ActorItr->GetName()))
		{
			//When the plane is found assign to Reference Plane.
			ReferencePlane = *ActorItr;
			break;
		}
	}*/
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AccumulatedDeltaTime += DeltaTime;

	if((AccumulatedDeltaTime >= EnemySpawnTimeSeconds)
		&& (GetNumberOfEnemies() < MaxNumberOfEnemies))
	{
		SpawnEnemy();
		AccumulatedDeltaTime = 0.0f;
	}
}

