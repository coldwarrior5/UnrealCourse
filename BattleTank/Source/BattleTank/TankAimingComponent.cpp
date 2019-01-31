// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

EFiringStatus UTankAimingComponent::GetFiringState() const { return FiringStatus; }
bool UTankAimingComponent::IsLockedOnTarget() const { return FiringStatus == EFiringStatus::Ready; }
float UTankAimingComponent::GetTankShotRange() const { return TankShotRange; }

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	//  You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(GetWorld()->GetTimeSeconds() - LastFireTime < Barrel->GetReloadTime())
	{
		FiringStatus = EFiringStatus::Loading;
	}
	else if(IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Ready;
	}

	if (CurrentAmmo <= 0)
	{
		FiringStatus = EFiringStatus::NoAmmo;
	}
}

// Sets default values for this component's properties
void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
	LastBarrelPosition = Barrel->GetForwardVector();
}


void UTankAimingComponent::AimAt(FVector HitLocation) const
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity(0);
	const auto StartLocation = Barrel->GetSocketLocation(FName(TEXT("ProjectileSocket")));
	// const auto LaunchSpeed = UTankBarrel::GetProjectileSpeed();
	const auto LaunchSpeed = ProjectileSpeed;

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

void UTankAimingComponent::RotateAt(FVector HitLocation) const
{
	if (!ensure(Barrel)) { return; }
	const auto StartLocation = Barrel->GetSocketLocation(FName(TEXT("ProjectileSocket")));
	auto AimDirection = (HitLocation - StartLocation);
	AimDirection.Z = 0;
	AimDirection.Normalize();
	AdjustTurretForShot(AimDirection);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	if(FiringStatus != EFiringStatus::Loading && FiringStatus != EFiringStatus::NoAmmo)
	{
		//Barrel->Fire();
		Barrel->Fire(ProjectileSpeed);
		CurrentAmmo--;
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::AdjustTurretForShot(FVector AimDirection) const
{
	if (!ensure(Barrel && Turret)) { return; }
	// Work out difference between current barrel rotation, and LastBarrelPosition
	const auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	const auto AimAsRotator = AimDirection.Rotation();
	auto RotationDifference = AimAsRotator - BarrelRotator;
	RotationDifference.Normalize();

	Barrel->Elevate(RotationDifference.Pitch);
	Turret->Rotate(RotationDifference.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForwardVector = Barrel->GetForwardVector();
	const auto Result = !BarrelForwardVector.Equals(LastBarrelPosition, 0.001f);
	LastBarrelPosition = BarrelForwardVector;
	return Result;
}
