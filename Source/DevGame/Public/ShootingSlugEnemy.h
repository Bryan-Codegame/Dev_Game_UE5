// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "ShootingSlugEnemy.generated.h"
/**
 * 
 */
UCLASS()
class DEVGAME_API AShootingSlugEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShootingSlugEnemy();

private:
	void RunBehaviour() override;
};
