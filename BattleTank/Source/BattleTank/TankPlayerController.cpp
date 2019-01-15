// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
