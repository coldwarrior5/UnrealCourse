// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move the turret the right amount this frame
	// Given a max rotational speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	const auto RotationalChange = RelativeSpeed * MaxTurretSpeedPerSecond * GetWorld()->DeltaTimeSeconds;
	const auto RawYaw = RelativeRotation.Yaw + RotationalChange;
	auto NewRotation = RelativeRotation;
	NewRotation.Yaw = RawYaw;
	SetRelativeRotation(NewRotation);
}
