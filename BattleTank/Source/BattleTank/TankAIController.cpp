// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto ControlledTank = Cast<ATank>(GetPawn());
	const auto PlayerTank = GetPlayerTank();
	if(ControlledTank && PlayerTank)
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
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
