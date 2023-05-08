// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "GameFramework/Actor.h"
#include "JumpingShootingSlugEnemy.generated.h"

UCLASS()
class DEVGAME_API AJumpingShootingSlugEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpingShootingSlugEnemy();

private:
	void RunBehaviour() override;

};
