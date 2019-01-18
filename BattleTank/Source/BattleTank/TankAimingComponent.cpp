// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) const
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName(TEXT("ProjectileSocket")));

	// Calculate the out launch velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if( bHaveAimSolution )
	{
		const auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		AdjustTankForShot(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AdjustTankForShot(FVector AimDirection) const
{
	// Work out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto RotationDifference = AimAsRotator - BarrelRotator;
	RotationDifference.Normalize();

	Barrel->Elevate(RotationDifference.Pitch);
	Turret->Rotate(RotationDifference.Yaw);
}


