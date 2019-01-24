// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Loading,
	Aiming,
	Ready
};

// Forward declaration
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and methods
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);
	// Called every frame
	UFUNCTION(BlueprintCallable, Category = "Control")
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = "Control")
	void RotateAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = "Control")
	void Fire();

protected:
	// Needs to be protected so it can be accessed from the subclass that is the blueprint
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Ready;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void AdjustTurretForShot(FVector AimDirection);
	// Sets default values for this component's properties
	UTankAimingComponent();
};
