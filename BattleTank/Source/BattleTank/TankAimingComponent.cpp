// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "../../../../../../../../Program Files/Epic Games/UE_4.21/Engine/Plugins/Experimental/AlembicImporter/Source/ThirdParty/Alembic/AlembicDeploy/include/halfLimits.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Sets default values for this component's properties
void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity(0);
	const auto StartLocation = Barrel->GetSocketLocation(FName(TEXT("ProjectileSocket")));
	const auto LaunchSpeed = Barrel->GetProjectileSpeed();

	// Calculate the out launch velocity
	const auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
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
	if (bHaveAimSolution)
	{
		const auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		AdjustTurretForShot(AimDirection);
	}
	else
	{
		RotateAt(HitLocation);
	}
}

void UTankAimingComponent::RotateAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	const auto StartLocation = Barrel->GetSocketLocation(FName(TEXT("ProjectileSocket")));
	auto AimDirection = (HitLocation - StartLocation);
	AimDirection.Z = 0;
	AimDirection.Normalize();
	AdjustTurretForShot(AimDirection);
}

void UTankAimingComponent::Fire() const
{
	if (!ensure(Barrel)) { return; }
	Barrel->Fire();
}

void UTankAimingComponent::AdjustTurretForShot(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	// Work out difference between current barrel rotation, and AimDirection
	const auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	const auto AimAsRotator = AimDirection.Rotation();
	auto RotationDifference = AimAsRotator - BarrelRotator;
	RotationDifference.Normalize();

	if(!FMath::IsNearlyZero(RotationDifference.Pitch, 0.1f) ||  !FMath::IsNearlyZero(RotationDifference.Yaw, 0.1f))
	{
		FiringStatus = EFiringStatus::Aiming;
		Barrel->Elevate(RotationDifference.Pitch);
		Turret->Rotate(RotationDifference.Yaw);
	}
	else
	{
		FiringStatus = EFiringStatus::Ready;
	}
	
}