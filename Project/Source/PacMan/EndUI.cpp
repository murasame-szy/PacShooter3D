// Fill out your copyright notice in the Description page of Project Settings.


#include "EndUI.h"

UEndUI::UEndUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    RestartBtn = Cast<UButton>(GetWidgetFromName("RestartBtn"));
    ExitBtn = Cast<UButton>(GetWidgetFromName("ExitBtn"));
    GameModeRef = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void UEndUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (RestartBtn)
    {
        FScriptDelegate Del;
        Del.BindUFunction(this, "Restart");
        RestartBtn->OnClicked.Add(Del);
    }
    if (ExitBtn)
    {
        FScriptDelegate Del;
        Del.BindUFunction(this, "Exit");
        ExitBtn->OnClicked.Add(Del);
    }
}

void UEndUI::Restart()
{
    GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
    RemoveFromParent();
    GetOwningPlayer()->bShowMouseCursor = false;
    GameModeRef->RestartGame();
}

void UEndUI::Exit()
{
    GameModeRef->ExitGame();
}
