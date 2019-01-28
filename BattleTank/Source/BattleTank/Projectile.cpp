// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Movement Component")));
	ProjectileMovementComponent->bAutoActivate = false;		// It doesn't fly off until we activate it
}

void AProjectile::LaunchProjectile(float Speed) const
{
	UE_LOG(LogTemp, Warning, TEXT("%f: projectile speed"), Speed)
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
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

