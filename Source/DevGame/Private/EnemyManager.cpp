// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EngineUtils.h"
// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int AEnemyManager::GetNumberOfEnemies() const
{
	return 0;
}


void AEnemyManager::SpawnEnemy()
{
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
	const FString EnemySpawnPlaneString = FString(TEXT("EnemySpawnPlane"));

	//Search the EnemySpawnPlane in the world 
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if(EnemySpawnPlaneString.Equals(ActorItr->GetName()))
		{
			//When the plane is found assign to Reference Plane.
			ReferencePlane = *ActorItr;
			break;
		}
	}
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

