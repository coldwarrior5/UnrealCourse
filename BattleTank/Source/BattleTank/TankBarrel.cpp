// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Projectile.h"

float UTankBarrel::GetProjectileSpeed() const { return ProjectileSpeed; }

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxBarrelSpeedPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawPitch = RelativeRotation.Pitch + ElevationChange;
	FRotator NewElevation = RelativeRotation;
	NewElevation.Pitch = FMath::Clamp<float>(RawPitch, MinElevationInDegrees, MaxElevationInDegrees);
	SetRelativeRotation(NewElevation);
}

void UTankBarrel::Fire()
{
	if (!ensure(ProjectileBlueprint))
	{
		UE_LOG(LogTemp, Error, TEXT("Tanks are not assigned projectile blueprint!"));
		return;
	}

	const auto IsReady = GetWorld()->GetTimeSeconds() - LastFireTime > ReloadTimeInSeconds;

	if(IsReady)
	{
		// Spawn a projectile at the socket location of the barrel
		const auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			this->GetSocketLocation(FName(TEXT("ProjectileSocket"))),
			this->GetSocketRotation(FName(TEXT("ProjectileSocket")))
			);
		Projectile->LaunchProjectile(ProjectileSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}
