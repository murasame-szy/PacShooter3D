// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PacManEnemy.generated.h"

UCLASS()
class PACMAN_API APacManEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* EnemyDisplayMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NormalSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float VulnerableSpeed;

	bool bIsDead;
	bool bIsVulnerable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeadTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float VulnerableTime;

	FTimerHandle DeadTimerHandle;
	FTimerHandle VulnerableTimerHandle;

	void SetPlayerlocation(FVector value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector playerLocation;

	UFUNCTION()
		void OnEnemyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetVulnerable(bool bRestoreTimer = false, float Time = 0.0f);
	void SetDead(bool bRestoreTimer = false, float Time = 0.0f);
	void SetNormal();
	void SetMovement(bool bCanMove);

private:
	FVector StartLocation;

};
