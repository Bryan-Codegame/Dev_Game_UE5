// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingSlugEnemy.h"

// Sets default values
// Invoke the parent constructor in the initialization list
AShootingSlugEnemy::AShootingSlugEnemy() : Super()
{
}

void AShootingSlugEnemy::RunBehaviour()
{
	//Super::RunBehaviour(); (This line closed the editor)
	// If fire interval has elapsed, spawn a new enemy projectile
	if (AccumulatedDeltaTime >= FireTimeInterval) {
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 250.0f;
		FRotator SpawnRotation = GetActorRotation();

		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);

		AccumulatedDeltaTime = 0.0f;
	}
}
