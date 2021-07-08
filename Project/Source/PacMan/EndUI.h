// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "EndUI.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API UEndUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UEndUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Meta = (BindWidget))
		UButton* RestartBtn;

	UPROPERTY(Meta = (BindWidget))
		UButton* ExitBtn;

protected:
	virtual void NativeConstruct() override;

	APacManGameModeBase* GameModeRef;

	UFUNCTION()
		void Restart();

	UFUNCTION()
		void Exit();

	
};
