// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pacdot.h"
#include "Projectile.h"
#include "PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PacManPlayer.generated.h"

UCLASS()
class PACMAN_API APacManPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* PacmanDisplayMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* PacmanEyeMesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* PacmanEyeMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Lives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NormalSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LowSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InvincibleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LowSpeedTime;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LauchSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShootTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShootColdDown;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Injured();
	void Resetting();
	void SetMovement(bool bCanMove);
	void StopShoot();
	void RemoveColdDown();
	void SetLowSpeed();
	void SetNormalSpeed();

	void StartGame();
	void PauseGame();
	void RestartGame();
	void Fire();

	void MoveX(float value);
	void MoveY(float value);

	UFUNCTION()
	void OnPacmanBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector Velocity;
	FVector StartLocation;
	APacManGameModeBase* GameModeRef;
	FTimerHandle ResettingTimerHandle;
	bool bCanShoot;
	bool bColdDown;
	FTimerHandle ShootTimerHandle;
	FTimerHandle LowSpeedTimerHandle;
	FTimerHandle ShootColdDownTimerHandle;
};
