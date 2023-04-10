// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class DEVGAME_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();
	
private:
	float AccumulatedDeltaTime;
	float EnemySpawnTimeSeconds;
	int MaxNumberOfEnemies;

	//TWeakObjectPtr<AActor> ReferencePlane;

	int GetNumberOfEnemies() const;
	FVector GetRandomLocationFromReferencePlane() const;
	void SpawnEnemy();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TWeakObjectPtr<AActor> ReferencePlane;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<class AActor> EnemyClass;
};
