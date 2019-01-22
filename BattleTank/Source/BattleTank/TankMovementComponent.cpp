// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

// +1 makes the take move forwards, whereas -1 makes it move backwards
void UTankMovementComponent::IntendMoveForward(float Throw) const
{
	if (!LeftTrack || !RightTrack) { return; }
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
}

// +1 makes the tank move to the right, whereas -1 makes it move to the left
void UTankMovementComponent::IntendMoveToTheSide(float Throw) const
{
	if (!LeftTrack || !RightTrack) { return; }
	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we are replacing the functionality
	const auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s: MoveVelocity: %s"), *TankName, *MoveVelocity.ToString());
}
