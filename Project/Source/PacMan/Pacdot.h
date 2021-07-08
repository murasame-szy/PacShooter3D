// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pacdot.generated.h"

UCLASS(Blueprintable)
class PACMAN_API APacdot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APacdot();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* PacdotDisplayMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent* PacdotCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsSuperPacdot = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
