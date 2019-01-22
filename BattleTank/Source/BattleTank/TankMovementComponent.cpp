// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) const
{
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward %f"), Throw)
}

void UTankMovementComponent::IntendMoveToTheSide(float Throw) const
{
	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);
	UE_LOG(LogTemp, Warning, TEXT("IntendMoveToTheSide %f"), Throw)
}
