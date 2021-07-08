// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManEnemy.h"
#include "PacManPlayer.h"

// Sets default values
APacManEnemy::APacManEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NormalSpeed = 600.0f;
	VulnerableSpeed = 300.0f;
	bIsDead = false;
	bIsVulnerable = false;
	DeadTime = 5.0f;
	VulnerableTime = 5.0f;
	EnemyDisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyDisplayMesh"));
	EnemyDisplayMesh->SetupAttachment(GetCapsuleComponent());

}

void APacManEnemy::SetPlayerlocation(FVector value)
{
	playerLocation = value;
}

// Called when the game starts or when spawned
void APacManEnemy::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManEnemy::OnEnemyBeginOverlap);
	SetMovement(true);
}

// Called every frame
void APacManEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacManEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APacManEnemy::OnEnemyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APacManPlayer::StaticClass()))
	{
		if (bIsDead)
		{
			return;
		}
		/*if (bIsVulnerable)
		{
			SetDead();
		}*/
		else
		{
			Cast<APacManPlayer>(OtherActor)->Injured();
		}
	}
	if (OtherActor->IsA(AProjectile::StaticClass()))
	{
		if (bIsDead)
		{
			return;
		}
		if (bIsVulnerable)
		{
			SetDead();
		}
		else
		{
			SetVulnerable();
		}
		OtherActor->Destroy();
	}

}

void APacManEnemy::SetVulnerable(bool bRestoreTimer, float Time)
{
	if (bRestoreTimer)
	{
		GetWorldTimerManager().SetTimer(VulnerableTimerHandle, this, &APacManEnemy::SetNormal, Time, false);
	}
	else
	{
		GetWorldTimerManager().SetTimer(VulnerableTimerHandle, this, &APacManEnemy::SetNormal, VulnerableTime, false);
	}
	if (bIsVulnerable)
	{
		return;
	}
	bIsVulnerable = true;
	SetMovement(true);
}

void APacManEnemy::SetDead(bool bRestoreTimer, float Time)
{
	if (bRestoreTimer && bIsDead)
	{
		GetWorldTimerManager().SetTimer(DeadTimerHandle, this, &APacManEnemy::SetNormal, Time, false);
		return;
	}
	bIsDead = true;
	SetMovement(true);
	SetActorLocation(StartLocation);
	GetWorldTimerManager().ClearTimer(VulnerableTimerHandle);
	GetWorldTimerManager().SetTimer(DeadTimerHandle, this, &APacManEnemy::SetNormal, DeadTime, false);
}

void APacManEnemy::SetNormal()
{
	GetWorldTimerManager().ClearTimer(DeadTimerHandle);
	GetWorldTimerManager().ClearTimer(VulnerableTimerHandle);
	bIsDead = false;
	bIsVulnerable = false;
	SetMovement(true);
}

void APacManEnemy::SetMovement(bool bCanMove)
{
	if (bCanMove)
	{
		if (!bIsVulnerable && !bIsDead)
		{
			GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
		}
		if (bIsVulnerable && !bIsDead)
		{
			GetCharacterMovement()->MaxWalkSpeed = VulnerableSpeed;
		}
		if (bIsDead)
		{
			GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		}
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
	}
}

