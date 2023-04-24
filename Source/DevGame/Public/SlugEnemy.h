// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlugEnemy.generated.h"

UCLASS()
class DEVGAME_API ASlugEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlugEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	// Any Object that has at least one valid pointer stored inside a UPROPERTY will not be Garbage Collected (GC). 
	// Non-UPROPERTY variables will not be counted by the GC system.
	// - https://wiki.unrealengine.com/UPROPERTY#Garbage_Collection
	// It cannot be declared as a TSharedPtr; UPROPERTIES are smart pointers implicitly, and so they follow another life cycle

	//We use UPROPERTY to free memory with the Garbage Collected
	UPROPERTY()
	TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	UPROPERTY()
	TWeakObjectPtr<UAnimSequence> IdleAnimation;
	UPROPERTY()
	TWeakObjectPtr<UParticleSystem> ExplosionParticleSystem;

	// Template it to allow UClass's to be passed around with type safety instead of using UClass*
	TSubclassOf<AActor> ProjectileClass;

	// A reference to the main player for enemies to look at him
	TWeakObjectPtr<APawn> PlayerPawn;

	float AccumulatedDeltaTime;

	float const FireTimeInterval = 2.0f;

};
