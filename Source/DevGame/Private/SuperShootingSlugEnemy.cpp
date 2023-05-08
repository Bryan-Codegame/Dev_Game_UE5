// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperShootingSlugEnemy.h"
#include "Components/PrimitiveComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ASuperShootingSlugEnemy::ASuperShootingSlugEnemy() : Super()
{
	TWeakObjectPtr<UMaterialInstanceDynamic> Material = SkeletalMesh->CreateAndSetMaterialInstanceDynamic(0);
	Material->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(1.0f, 0.0f, 0.0f));
}

void ASuperShootingSlugEnemy::RunBehaviour()
{
	// If fire interval has elapsed, spawn 3 enemy projectiles
	if (AccumulatedDeltaTime >= FireTimeInterval) {
		FVector SpawnLocation1 = GetActorLocation() + GetActorForwardVector() * 250.0f;
		FVector SpawnLocation2 = GetActorLocation() + GetActorForwardVector() * 500.0f;
		FVector SpawnLocation3 = GetActorLocation() + GetActorForwardVector() * 750.0f;
		FRotator SpawnRotation1 = GetActorRotation();
		FRotator SpawnRotation2 = GetActorRotation().Add(0.0f, 15.0f, 0.0f);
		FRotator SpawnRotation3 = GetActorRotation().Add(0.0f, -15.0f, 0.0f);

		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation1, &SpawnRotation1);
		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation2, &SpawnRotation2);
		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation3, &SpawnRotation3);

		AccumulatedDeltaTime = 0.0f;
	}
}



