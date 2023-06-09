// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpingShootingSlugEnemy.h"

// Sets default values
AJumpingShootingSlugEnemy::AJumpingShootingSlugEnemy() : Super()
{
	TWeakObjectPtr<UMaterialInstanceDynamic> Material = SkeletalMesh->CreateAndSetMaterialInstanceDynamic(0);
	Material->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(0.0f, 1.0f, 0.0f));
}

void AJumpingShootingSlugEnemy::RunBehaviour()
{
	// Cast a ray from the enemy to the ground, to know if he stands on the ground or not
	float Offset = 70.0f;
	FHitResult HitResult;
	auto Start = GetActorLocation() + (GetActorUpVector() * Offset);  // The raycast has to start in the geometry origin of the actor
	auto End = Start + (-1 * GetActorUpVector() * 100.0f);
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bTraceComplex = true;

	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, TraceParams);
	if (Hit) {
		
		// If it's on the ground, make it jumps
		if (HitResult.Distance <= Offset + 10.0f) {  // Add 10 units to be safe in case the actor fall into a slope
			//SkeletalMesh->AddImpulse(GetActorUpVector() * SkeletalMesh->GetMass() * 1000.0f);
		}
		SkeletalMesh->AddImpulse(GetActorUpVector() * SkeletalMesh->GetMass() * 700.0f);
		//Draw raycast on game
		DrawDebugLine(GetWorld(), Start, End, FColor(255, 0, 0),false,
			-1, 0, 9);
	}
	else
	{
		DrawDebugLine(GetWorld(), Start, End, FColor(255, 255, 0),false,
			-1, 0, 9);
	}

	
	DrawDebugLine(
			GetWorld(),
			Start,
			Start - (GetActorUpVector()*(Offset+10.0f)),
			FColor(0, 255, 0),
			false, -1, 0,
			12
		
			);
	

	// If fire interval has elapsed, spawn a new enemy projectile
	if (AccumulatedDeltaTime >= FireTimeInterval) {
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 250.0f;
		FRotator SpawnRotation = GetActorRotation();

		GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);

		AccumulatedDeltaTime = 0.0f;
	}
}


