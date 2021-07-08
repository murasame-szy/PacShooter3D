// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class PACMAN_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ProjectileDisplayMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent* ProjectileCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float RemainTime;

	void launchProjectile(float Speed);

	void SetMovement(float Speed);

	FTimerHandle RemainTimerHandle;

	void DestroySelf();

};
