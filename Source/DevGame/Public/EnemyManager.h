// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class ABaseEnemy;

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

	int GetNumberOfEnemies() const;
	FVector GetRandomLocationFromReferencePlane() const;
	TSubclassOf<ABaseEnemy> GetRandomEnemyClass() const;
	void SpawnEnemy();
	
	// Keeps a list of enemy types to spawn
	TArray<TSubclassOf<ABaseEnemy>> EnemyClasses;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Invisible plane (static mesh actor) to spawn enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TWeakObjectPtr<AActor> ReferencePlane;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<class AActor> EnemyClass;
};
