// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	float GetProjectileSpeed() const;
	// -1 is max downward speed, and +1 is max up speed
	void Elevate(float RelativeSpeed);
	void Fire();

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxBarrelSpeedPerSecond = 8;	// Sensible default value of 5 deg/s
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationInDegrees = 0;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationInDegrees = 40;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;		// This ensures that designer in Blueprint cannot assign wrong class
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 5;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileSpeed = 4000;

	float LastFireTime = -ReloadTimeInSeconds;
};
