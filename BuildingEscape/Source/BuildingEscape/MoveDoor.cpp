// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UMoveDoor::UMoveDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMoveDoor::BeginPlay()
{
	Super::BeginPlay();
	OwningDoor = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if(PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Check if it is time to close the door

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		CloseDoor();
	
}

void UMoveDoor::OpenDoor() const
{
	OwningDoor->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UMoveDoor::CloseDoor() const
{
	OwningDoor->SetActorRotation(FRotator(0.0f, ClosedAngle, 0.0f));
}