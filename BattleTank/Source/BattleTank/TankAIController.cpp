#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	const auto PlayerTank = GetPlayerTank();
	if(ensure(AimingComponent && PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);		// Pathfinding system
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		AimingComponent->Fire();
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
