#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto ControlledTank = Cast<ATank>(GetPawn());
	const auto PlayerTank = GetPlayerTank();
	if(ensure(ControlledTank && PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);		// Pathfinding system
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	
	if(ensure(PlayerController))
	{
		APawn* Pawn = PlayerController->GetPawn();
		if(Pawn)
		{
			return Cast<ATank>(Pawn);
		}
	}
	return nullptr;
}
