// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacManEnemy.h"
#include "Pacdot.h"
#include "EnemyController.h"
#include "Projectile.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Public/EngineUtils.h"
#include "PacManGameModeBase.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGameState : uint8
{
	EMenu,
	EPlay,
	EPause,
	EWin,
	EGameover
};

UCLASS()
class PACMAN_API APacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APacManGameModeBase();

protected:
	virtual void BeginPlay() override;

public:
	void StartGame();
	void PauseGame();
	void RestartGame();
	void ExitGame();

	int GetPacdotNum() const;
	void SetPacdotNum(int value);

	EGameState GetCurState();
	void SetCurState(EGameState value);

	void SetEnemiesVulnerable();

	//void InitLevelInfo();

	//void RecordEnemiesTimer();
	//void RestoreEnemiesTimer();

	//void RecordProjectilesInfo();
	//void RestoreProjectilesInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EGameState curState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int pacdotNum;

private:
	TArray<APacManEnemy*> Enemies;
	//TArray<AProjectile*> Projectiles;
	//TArray<float> EnemiesTimerRemaining;

	//TArray<float> ProjectileSpeed;

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		//TSubclassOf<class UUserWidget> wPauseMenu;

	//UUserWidget* MainMenu;
	UUserWidget* MainUI;
	UUserWidget* PauseMenu;
	UUserWidget* EndMenu;

//1.1
public:
	void SetPlayerLocation(FVector value);

	FVector playerLocation;
};
