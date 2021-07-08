// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"


void AEnemyController::OnPossess(APawn* PawnControlled)
{
	Super::OnPossess(PawnControlled);

	ControlledEnemy = Cast<APacManEnemy>(PawnControlled);
}

void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	GotoNewDestiantion();
}

void AEnemyController::GotoNewDestiantion()
{
	UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(this);

	if (NavMesh)
	{
		FNavLocation RandomLocation;
		const bool bGetNewDesination = NavMesh->GetRandomReachablePointInRadius(
			ControlledEnemy->playerLocation, SearchRadius, RandomLocation);
		if (bGetNewDesination)
		{
			MoveToLocation(RandomLocation.Location, 50.0f);
		}
	}
	
	//1.0
	/*if (NavMesh)
	{
		FNavLocation RandomLocation;
		const bool bGetNewDesination =  NavMesh->GetRandomReachablePointInRadius(
			ControlledEnemy->GetActorLocation(), SearchRadius, RandomLocation);
		if (bGetNewDesination)
		{
			MoveToLocation(RandomLocation.Location, 50.0f);
		}
	}*/
}
