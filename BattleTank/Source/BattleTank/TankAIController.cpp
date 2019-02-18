#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"		// So we can implement OnDeath
// Depends on movement component via path-finding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	TankShotRange = AimingComponent->GetTankShotRange();
	const auto PlayerTank = GetPlayerTank();
	if(AimingComponent && PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);		// Path-finding system
		const auto PlayerLocation = PlayerTank->GetActorLocation();
		if(FVector::Dist(PlayerLocation, GetPawn()->GetActorLocation()) > TankShotRange)
			return;
		AimingComponent->AimAt(PlayerLocation);
		if(AimingComponent->IsLockedOnTarget())
			AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if(InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if(!PossessedTank) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

APawn* ATankAIController::GetPlayerTank() const
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	
	if(PlayerController)
	{
		const auto Pawn = PlayerController->GetPawn();
		if(Pawn)
		{
			return Pawn;
		}
	}
	return nullptr;
}
