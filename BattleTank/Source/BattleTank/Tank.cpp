// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
void ATank::AimAt(FVector HitLocation) const
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation);
}

void ATank::RotateAt(FVector HitLocation) const
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->RotateAt(HitLocation);
}

void ATank::Fire() const
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->Fire();
}
