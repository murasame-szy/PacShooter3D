// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PauseUI.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API UPauseUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPauseUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Meta = (BindWidget))
		UButton* StartGameBtn;

	UPROPERTY(Meta = (BindWidget))
		UButton* ExitBtn;

protected:
	virtual void NativeConstruct() override;

	APacManGameModeBase* GameModeRef;

	UFUNCTION()
		void GoOn();
	
	UFUNCTION()
		void Exit();
	
};
