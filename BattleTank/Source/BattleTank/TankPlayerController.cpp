// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	const auto ControlledTank = GetControlledTank();
	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("The tank pawn is not attached to the player controller"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Tank pawn found: %s"), *ControlledTank->GetName());

}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimAtReticle();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtReticle() const
{
	const auto ControlledTank = GetControlledTank();
	if(!ControlledTank){ return; }

	FVector HitLocation; // Out parameter
	if(FindSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Get world location of line-trace through reticle
// Returns true if it hits landscape

bool ATankPlayerController::FindSightRayHitLocation(FVector& OutHitLocation) const
{
	//auto EyeLocation = GetControlledTank()->GetPawnViewLocation();
	FVector LookDirection;
	FVector2D ScreenLocation = GetReticleScreenLocation();

	// Deproject the screen position of the reticle to a world direction
	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}

// Find tje reticle position in pixel coordinates
FVector2D ATankPlayerController::GetReticleScreenLocation() const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	return FVector2D(ViewportSizeX * ReticleXLocation, ViewportSizeY * ReticleYLocation);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector EyeLocation = PlayerCameraManager->GetCameraLocation();
	FVector RangeEndLocation = EyeLocation + LookDirection * TankShotRange;
	FCollisionQueryParams Params(TEXT(""), false, GetPawn());	// We want to ignore the player pawn when line tracing

	if(GetWorld()->LineTraceSingleByChannel(
		HitResult,
		EyeLocation,
		RangeEndLocation,
		ECollisionChannel::ECC_Visibility,
		Params
	))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	else
	{
		OutHitLocation = FVector(0);
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector LookLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, LookLocation, LookDirection);
}
