// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		float HandReach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Find (assumed) attached physics handle
	void FindPhysicsHandleComponent();
	// Setup (assumed) attached input component
	void SetupInputComponent();
	// Ray-cast and grab what is within reach
	void Grab();
	// Called when grab is released
	void Release();
	// Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;
	FVector GetLineTraceStart() const;
	// Calculate the Reach vector using HandReach variable and viewport location and rotation
	FVector GetLineTraceEnd() const;
};