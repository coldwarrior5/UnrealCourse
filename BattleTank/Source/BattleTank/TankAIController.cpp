#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
// Depends on movement component via path-finding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	const auto PlayerTank = GetPlayerTank();
	if(ensure(AimingComponent && PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);		// Path-finding system
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		AimingComponent->Fire();
	}
}

APawn* ATankAIController::GetPlayerTank() const
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	
	if(ensure(PlayerController))
	{
		const auto Pawn = PlayerController->GetPawn();
		if(Pawn)
		{
			return Pawn;
		}
	}
	return nullptr;
}
