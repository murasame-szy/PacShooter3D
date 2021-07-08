// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseUI.h"

UPauseUI::UPauseUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    StartGameBtn = Cast<UButton>(GetWidgetFromName("StartGameBtn"));
    ExitBtn = Cast<UButton>(GetWidgetFromName("ExitBtn"));
    GameModeRef = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
}


void UPauseUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (StartGameBtn)
    {
        FScriptDelegate Del;
        Del.BindUFunction(this, "GoOn");
        StartGameBtn->OnClicked.Add(Del);
    }
    if (ExitBtn)
    {
        FScriptDelegate Del;
        Del.BindUFunction(this, "Exit");
        ExitBtn->OnClicked.Add(Del);
    }
}

void UPauseUI::GoOn()
{
    GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
    RemoveFromParent();
    GetOwningPlayer()->bShowMouseCursor = false;
    UGameplayStatics::SetGamePaused(this, false);
    GameModeRef->SetCurState(EGameState::EPlay);
}

void UPauseUI::Exit()
{
    GameModeRef->ExitGame();
}
