// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UCLASS(Abstract)
class DEVGAME_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TWeakObjectPtr<UAnimSequence> IdleAnimation;
	UPROPERTY()
	TWeakObjectPtr<UParticleSystem> ExplosionParticleSystem;

protected:
	UFUNCTION()
	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	// (2) 
	// ... so, in order to create pure virtual functions (i.e., functions that
	// must be implemented in child classes), UE4 provides the PURE_VIRTUAL(function, default_code)
	// macro. Watch out for the mandatory comma!
	virtual void RunBehaviour() PURE_VIRTUAL(ABaseEnemy::RunBehaviour, );

	UPROPERTY()
	TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	TSubclassOf<AActor> ProjectileClass;
	TWeakObjectPtr<APawn> PlayerPawn;
	float AccumulatedDeltaTime;

	float const FireTimeInterval = 2.0f;
};
