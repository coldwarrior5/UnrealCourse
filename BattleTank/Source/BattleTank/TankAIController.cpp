// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	const auto PlayerTank = GetPlayerTank();

	if(PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy found"), *PlayerTank->GetName());

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI hasn't found enemy player."));

	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	
	if(PlayerController)
	{
		APawn* Pawn = PlayerController->GetPawn();
		if(Pawn)
		{
			return Cast<ATank>(Pawn);
		}
	}
	return nullptr;
}
