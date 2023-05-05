// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set the first component, i.e., the root node (it can be whatever component type)
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Models/Slug/SlugGoodOrientation/Slug.Slug'"));
	
	if (MeshAsset.Succeeded())
	{
		SkeletalMesh->SetSkeletalMesh(MeshAsset.Object);
		SkeletalMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
		//SkeletalMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	}

	// Set the physics asset, i.e., for collision shapes, gravity, etc
	auto PhysicsAsset = ConstructorHelpers::FObjectFinder<UPhysicsAsset>(TEXT("PhysicsAsset'/Game/Models/Slug/SlugGoodOrientation/Slug_PhysicsAsset.Slug_PhysicsAsset'"));
	
	if (PhysicsAsset.Succeeded())
	{
		SkeletalMesh->SetPhysicsAsset(PhysicsAsset.Object);
		SkeletalMesh->SetSimulatePhysics(true);
		SkeletalMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
		SkeletalMesh->BodyInstance.bLockXRotation = true;
		SkeletalMesh->BodyInstance.bLockYRotation = true;
		SkeletalMesh->BodyInstance.bLockXTranslation = true;
		SkeletalMesh->BodyInstance.bLockYTranslation = true;
	}

	// Set the animation to play
	auto AnimAsset = ConstructorHelpers::FObjectFinder<UAnimSequence>(TEXT("AnimSequence'/Game/Models/Slug/SlugGoodOrientation/Slug_Anim_armature_Idle.Slug_Anim_armature_Idle'"));
	
	if (AnimAsset.Succeeded())
	{
		IdleAnimation = AnimAsset.Object;
	}

	// Set the particle system to play on destroy
	auto ParticleSystemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'"));
	if (ParticleSystemAsset.Succeeded())
	{
		ExplosionParticleSystem = ParticleSystemAsset.Object;
	}
	

	// Set collision callback method for on hit events on actor from projectile blueprints
	OnActorHit.AddDynamic(this, &ThisClass::OnHit);

	//Set Projectile Class
	//TODO Create a BP Projectile class from c++ class and try with this part of code
	//I will enable this part of code when I want to get a reference from some BP class created in editor 
	auto FirstPersonProjectileBPClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonProjectile"));
	
	if (FirstPersonProjectileBPClass.Succeeded()) {
		ProjectileClass = FirstPersonProjectileBPClass.Class;
	}

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;

	// Cache enemy location to use it later
	FVector EnemyLocation = GetActorLocation();

	//To get the correct orientation of Slug we have to import it with 90 degrees on axis Z.
	// Rotate the enemy to face the player
	FRotator EnemyRotation = FRotationMatrix::MakeFromX(PlayerPawn->GetActorLocation() - EnemyLocation).Rotator();
	SkeletalMesh->SetRelativeRotation(EnemyRotation, false, nullptr, ETeleportType::TeleportPhysics);

	RunBehaviour();

}

