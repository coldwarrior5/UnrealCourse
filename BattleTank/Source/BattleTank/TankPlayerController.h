// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// Must be the last include

class UTankAimingComponent;
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
public:
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(BlueprintReadWrite)
	float ReticleXLocation = 0.5;
	UPROPERTY(BlueprintReadWrite)
	float ReticleYLocation = 0.3;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	UTankAimingComponent* GetAimingComponent() const;
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void PlayerUIComponents(UTankAimingComponent* AimingCompReference, ATank* TankReference);

private:
	void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnPossessedTankDeath();
	void AimAtReticle() const;
	FVector2D GetReticleScreenLocation() const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
	bool FindSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	float TankShotRange = 0;
};