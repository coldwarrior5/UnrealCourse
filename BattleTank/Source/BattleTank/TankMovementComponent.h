// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * Responsible for driving the tank by controlling the tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw) const;
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveToTheSide(float Throw) const;

	// Overriding this method so that the AI players are constrained to the same behaviour as the players are
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
