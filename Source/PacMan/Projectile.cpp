// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	ProjectileDisplayMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("ProjectileDisplayMesh"));

	ProjectileDisplayMesh->SetupAttachment(ProjectileCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.8f;
	ProjectileMovementComponent->Friction = 0.0f;

	RemainTime = 2.0f;

	ProjectileCollision->SetSphereRadius(8.0f);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::launchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
	GetWorldTimerManager().SetTimer(RemainTimerHandle, this, &AProjectile::DestroySelf, RemainTime, false);
}

void AProjectile::SetMovement(float Speed)
{
	if (Speed)
	{
		ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
		ProjectileMovementComponent->Activate();
	}
	else
	{
		ProjectileMovementComponent->Deactivate();
	}
}

void AProjectile::DestroySelf()
{
	Destroy();
}

