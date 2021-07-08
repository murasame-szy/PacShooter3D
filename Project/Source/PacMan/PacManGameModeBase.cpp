// Copyright Epic Games, Inc. All Rights Reserved.


#include "PacManGameModeBase.h"
#include "PacManPlayer.h"

APacManGameModeBase::APacManGameModeBase()
{
	SetCurState(EGameState::EMenu);
}

void APacManGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainUI)
	{
		MainUI->RemoveFromViewport();
		MainUI = nullptr;
	}
	if (UClass* MyWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprints/WBP_MainUI.WBP_MainUI_C'")))
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			MainUI = CreateWidget<UUserWidget>(PC, MyWidgetClass);
			if (MainUI)
			{
				MainUI->AddToViewport();
				PC->bShowMouseCursor = false;
				PC->SetInputMode(FInputModeGameOnly());
			}
		}
	}
	/*if (MainMenu)
	{
		MainMenu->RemoveFromViewport();
		MainMenu = nullptr;
	}
	if (UClass* MyWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprints/WBP_MainMenu.WBP_MainMenu_C'")))
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			MainMenu = CreateWidget<UUserWidget>(PC, MyWidgetClass);
			if (MainMenu)
			{
				MainMenu->AddToViewport();
				PC->bShowMouseCursor = false;
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}*/


	for (TActorIterator<APacdot> PacdotItr(GetWorld()); PacdotItr; ++PacdotItr)
	{
		pacdotNum++;
	}

	for (TActorIterator<APacManEnemy> EnemyItr(GetWorld()); EnemyItr; ++EnemyItr)
	{
		Enemies.Add(Cast<APacManEnemy>(*EnemyItr));
	}
}

void APacManGameModeBase::StartGame()
{
	if (curState == EGameState::EMenu)
	{
		SetCurState(EGameState::EPlay);
		for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
		{
			Cast<AEnemyController>((*Iter)->GetController())->GotoNewDestiantion();
		}
	}
}

void APacManGameModeBase::PauseGame()
{
	if (curState == EGameState::EPlay)
	{
		//RecordEnemiesTimer();
		//SetCurState(EGameState::EPause);
		/*UGameplayStatics::SetGamePaused(GetWorld(), true);
		SetCurState(EGameState::EPause);*/
		/*PauseMenu = CreateWidget<UUserWidget>(GetWorld(), wPauseMenu, "/Blueprints/WBP_PaueUI");
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();
		}
		SetCurState(EGameState::EPause);
		UGameplayStatics::SetGamePaused(this, true);*/
		if (PauseMenu)
		{
			PauseMenu->RemoveFromViewport();
			PauseMenu = nullptr;
		}
		if (UClass* MyWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprints/WBP_PauseUI.WBP_PauseUI_C'")))
		{
			if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
			{
				PauseMenu = CreateWidget<UUserWidget>(PC, MyWidgetClass);
				if (PauseMenu)
				{
					PauseMenu->AddToViewport();
					PC->bShowMouseCursor = true;
					PC->SetInputMode(FInputModeUIOnly());
					SetCurState(EGameState::EPause);
					UGameplayStatics::SetGamePaused(this, true);
				}
			}
		}
	}
	//else if (curState == EGameState::EPause)
	//{
	//	//RestoreEnemiesTimer();
	//	//SetCurState(EGameState::EPlay);
	//	UGameplayStatics::SetGamePaused(GetWorld(), false);
	//	SetCurState(EGameState::EPlay);
	//}
}

void APacManGameModeBase::RestartGame()
{
	GetWorld()->GetFirstLocalPlayerFromController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacManGameModeBase::ExitGame()
{
	GetWorld()->GetFirstLocalPlayerFromController()->ConsoleCommand(TEXT("QUIT"));
}

int APacManGameModeBase::GetPacdotNum() const
{
	return pacdotNum;
}

void APacManGameModeBase::SetPacdotNum(int value)
{
	pacdotNum = value;
	if (pacdotNum == 0)
	{
		SetCurState(EGameState::EWin);
	}
}

EGameState APacManGameModeBase::GetCurState()
{
	return curState;
}

void APacManGameModeBase::SetCurState(EGameState value)
{
	curState = value;

	switch (curState)
	{
		case EGameState::EPlay:
			/*for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
			{
				(*Iter)->SetMovement(true);
			}
			Cast<APacManPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn())->SetMovement(true);*/
			//UGameplayStatics::SetGamePaused(GetWorld(), false);
			break;
			/*for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
			{
				(*Iter)->SetMovement(false);
				GetWorldTimerManager().ClearAllTimersForObject(*Iter);
			}
			Cast<APacManPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn())->SetMovement(false);
			GetWorldTimerManager().ClearAllTimersForObject(GetWorld()->GetFirstPlayerController()->GetPawn());
			Projectiles.Empty();
			for (TActorIterator<AProjectile> ProjItr(GetWorld()); ProjItr; ++ProjItr)
			{
				Projectiles.Add(*ProjItr);
			}
			for (auto Iter(Projectiles.CreateIterator()); Iter; ++Iter)
			{
				(*Iter)->SetMovement(0.0f);
				GetWorldTimerManager().ClearAllTimersForObject(*Iter);
			}*/
			//UGameplayStatics::SetGamePaused(GetWorld(), true);
			break;
		case EGameState::EWin:
			for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
			{
				(*Iter)->Destroy();
			}
		case EGameState::EGameover:
			if (EndMenu)
			{
				EndMenu->RemoveFromViewport();
				EndMenu = nullptr;
			}
			if (UClass* MyWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprints/WBP_EndUI.WBP_EndUI_C'")))
			{
				if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
				{
					EndMenu = CreateWidget<UUserWidget>(PC, MyWidgetClass);
					if (EndMenu)
					{
						EndMenu->AddToViewport();
						PC->bShowMouseCursor = true;
						PC->SetInputMode(FInputModeUIOnly());
					}
				}
			}
			break;
		default:
			break;
	}
}

//void APacManGameModeBase::InitLevelInfo()
//{
//	for (TActorIterator<APacdot> PacdotItr(GetWorld()); PacdotItr; ++PacdotItr)
//	{
//		pacdotNum++;
//	}
//
//	for (TActorIterator<APacManEnemy> EnemyItr(GetWorld()); EnemyItr; ++EnemyItr)
//	{
//		Enemies.Add(Cast<APacManEnemy>(*EnemyItr));
//	}
//}

//void APacManGameModeBase::SetEnemiesVulnerable()
//{
//	for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
//	{
//		(*Iter)->SetVulnerable();
//	}
//}

//void APacManGameModeBase::RecordEnemiesTimer()
//{
//	EnemiesTimerRemaining.Empty();
//	for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
//	{
//		if (!(*Iter)->bIsVulnerable && !(*Iter)->bIsDead)
//		{
//			EnemiesTimerRemaining.Add(-1);
//		}
//		if ((*Iter)->bIsVulnerable && !(*Iter)->bIsDead)
//		{
//			float VulnerableTimerRemaining = GetWorldTimerManager().GetTimerRemaining((*Iter)->VulnerableTimerHandle);
//			EnemiesTimerRemaining.Add(VulnerableTimerRemaining);
//		}
//		if ((*Iter)->bIsDead)
//		{
//			float DeadTimerRemaing = GetWorldTimerManager().GetTimerRemaining((*Iter)->DeadTimerHandle);
//			EnemiesTimerRemaining.Add(DeadTimerRemaing);
//		}
//	}
//}
//
//void APacManGameModeBase::RestoreEnemiesTimer()
//{
//	for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
//	{
//		if ((*Iter)->bIsVulnerable && !(*Iter)->bIsDead)
//		{
//			(*Iter)->SetVulnerable(true, EnemiesTimerRemaining[Iter.GetIndex()]);
//		}
//		if ((*Iter)->bIsDead)
//		{
//			(*Iter)->SetDead(true, EnemiesTimerRemaining[Iter.GetIndex()]);
//		}
//	}
//}

//void APacManGameModeBase::RecordProjectilesInfo()
//{
//	ProjectileSpeed.Empty();
//	for (auto Iter(Projectiles.CreateIterator()); Iter; ++Iter)
//	{
//		/////////如何获取当前速度
//	}
//}

//void APacManGameModeBase::RestoreProjectilesInfo()
//{
//}

void APacManGameModeBase::SetPlayerLocation(FVector value)
{
	playerLocation = value;

	for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
	{
		APacManEnemy* Enemy = Cast<APacManEnemy>(*Iter);
		Enemy->SetPlayerlocation(playerLocation);
	}
}
