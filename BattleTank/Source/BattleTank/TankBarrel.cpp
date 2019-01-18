// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

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
