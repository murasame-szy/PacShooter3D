// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PacManEnemy.h"
#include "NavigationSystem.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	void OnPossess(APawn* PawnControlled) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void GotoNewDestiantion();


private:
	APacManEnemy* ControlledEnemy;
	float SearchRadius = 300.0f;
};
