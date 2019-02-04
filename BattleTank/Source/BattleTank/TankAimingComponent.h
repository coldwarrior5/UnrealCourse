// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	NoAmmo,
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
	void AimAt(FVector HitLocation) const;
	UFUNCTION(BlueprintCallable, Category = "Control")
	void RotateAt(FVector HitLocation) const;
	UFUNCTION(BlueprintCallable, Category = "Control")
	void Fire();

	EFiringStatus GetFiringState() const;
	bool IsLockedOnTarget() const;
	float GetTankShotRange() const;

protected:
	// Needs to be protected so it can be accessed from the subclass that is the blueprint
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Loading;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float TankShotRange = 100000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileSpeed = 8000;
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentAmmo() const { return CurrentAmmo; }
	UFUNCTION(BlueprintCallable)
	int32 GetTotalAmmo() const { return TotalAmmo; }

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	float LastFireTime = 0;
	FVector LastBarrelPosition;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 TotalAmmo = 100;
	int32 CurrentAmmo = TotalAmmo;

	void AdjustTurretForShot(FVector AimDirection) const;
	// Sets default values for this component's properties
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool IsBarrelMoving();

};
