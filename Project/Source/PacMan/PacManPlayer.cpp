// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManPlayer.h"

// Sets default values
APacManPlayer::APacManPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Velocity = FVector(0.0f, 0.0f, 0.0f);
	Lives = 3;
	NormalSpeed = 600.f;
	LowSpeed = 300.0f;
	InvincibleTime = 2.0f;
	LauchSpeed = 900.0f;
	bCanShoot = false;
	bColdDown = false;
	ShootTime = 5.0f;
	LowSpeedTime = 1.0f;
	ShootColdDown = 0.2f;

	GetCapsuleComponent()->SetCapsuleHalfHeight(32.0f);
	GetCapsuleComponent()->SetCapsuleRadius(32.0f);

	PacmanDisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PacmanDispalyMesh"));
	PacmanDisplayMesh->SetupAttachment(GetCapsuleComponent());

	PacmanEyeMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eye1"));
	PacmanEyeMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eye2"));
	PacmanEyeMesh1->SetupAttachment(PacmanDisplayMesh);
	PacmanEyeMesh2->SetupAttachment(PacmanDisplayMesh);

	
}

// Called when the game starts or when spawned
void APacManPlayer::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	GameModeRef =Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManPlayer::OnPacmanBeginOverlap);
	SetMovement(true);
	
}

// Called every frame
void APacManPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameModeRef->SetPlayerLocation(GetActorLocation());
}

// Called to bind functionality to input
void APacManPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->SetTickableWhenPaused(true);

	PlayerInputComponent->BindAction("StartGame", IE_Pressed, this, &APacManPlayer::StartGame);
	PlayerInputComponent->BindAction("PauseGame", IE_Pressed, this, &APacManPlayer::PauseGame);
	PlayerInputComponent->BindAction("RestartGame", IE_Pressed, this, &APacManPlayer::RestartGame);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APacManPlayer::Fire);

	PlayerInputComponent->BindAxis("MoveX", this, &APacManPlayer::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APacManPlayer::MoveY);
}

void APacManPlayer::Injured()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Invincible"));
	--Lives;
	if (Lives == 0)
	{
		GameModeRef->SetCurState(EGameState::EGameover);
	}
	else
	{
		SetActorLocation(StartLocation);
		StopShoot();
		SetNormalSpeed();
		GetWorldTimerManager().SetTimer(ResettingTimerHandle, this, &APacManPlayer::Resetting, InvincibleTime, false);
	}
}

void APacManPlayer::Resetting()
{
	GetWorldTimerManager().ClearTimer(ResettingTimerHandle);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
}

void APacManPlayer::SetMovement(bool bCanMove)
{
	if (bCanMove)
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
	}
}

void APacManPlayer::StopShoot()
{
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	GetWorldTimerManager().ClearTimer(ShootColdDownTimerHandle);
	bCanShoot = false;
	bColdDown = false;
}

void APacManPlayer::RemoveColdDown()
{
	GetWorldTimerManager().ClearTimer(ShootColdDownTimerHandle);
	bColdDown = false;
}

void APacManPlayer::SetLowSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = LowSpeed;
	GetWorldTimerManager().SetTimer(LowSpeedTimerHandle, this, &APacManPlayer::SetNormalSpeed, LowSpeedTime, false);
}

void APacManPlayer::SetNormalSpeed()
{
	GetWorldTimerManager().ClearTimer(LowSpeedTimerHandle);
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

void APacManPlayer::StartGame()
{
	GameModeRef->StartGame();
}

void APacManPlayer::PauseGame()
{
	GameModeRef->PauseGame();
}

void APacManPlayer::RestartGame()
{
	GameModeRef->RestartGame();
}

void APacManPlayer::Fire()
{
	if (GameModeRef->GetCurState() == EGameState::EPlay && bCanShoot && !bColdDown)
	{
		if (ProjectileType == nullptr) return;
		//AProjectile* Projectile;
		FVector SpawnLocation = GetActorLocation() + 2 * GetCapsuleComponent()->GetScaledCapsuleRadius() * GetActorRotation().Vector();
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileType, SpawnLocation, GetActorRotation());
		Projectile->launchProjectile(LauchSpeed);
		bColdDown = true;
		GetWorldTimerManager().SetTimer(ShootColdDownTimerHandle, this, &APacManPlayer::RemoveColdDown, ShootColdDown, false);
	}
}

void APacManPlayer::MoveX(float value)
{
	if (GameModeRef->GetCurState() == EGameState::EPlay)
	{
		Velocity.X = value;
		Velocity.Y = 0;

		if (value > 0)
		{
			SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
		else if (value < 0)
		{
			SetActorRotation(FRotator(0.0f, -180.0f, 0.0f));
		}
		AddMovementInput(Velocity);
	}
}

void APacManPlayer::MoveY(float value)
{
	if (GameModeRef->GetCurState() == EGameState::EPlay)
	{
		Velocity.X = 0;
		Velocity.Y = value;

		if (value > 0)
		{
			SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
		}
		else if (value < 0)
		{
			SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
		}

		AddMovementInput(Velocity);
	}
}

void APacManPlayer::OnPacmanBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameModeRef->GetCurState() == EGameState::EPlay)
	{
		if (OtherActor->IsA(APacdot::StaticClass()))
		{
			APacdot* curPacdot = Cast<APacdot>(OtherActor);
			if (curPacdot->bIsSuperPacdot)
			{
				//GameModeRef->SetEnemiesVulnerable();
				bCanShoot = true;
				GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &APacManPlayer::StopShoot, ShootTime, false);
			}
			OtherActor->Destroy();
			GameModeRef->SetPacdotNum(GameModeRef->GetPacdotNum() - 1);
		}
		if (OtherActor->IsA(AProjectile::StaticClass()))
		{
			SetLowSpeed();
		}
	}
}
