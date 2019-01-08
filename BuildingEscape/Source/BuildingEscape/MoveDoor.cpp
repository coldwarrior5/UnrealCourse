// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
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

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing pressure plate component"), *OwningDoor->GetName())
	}
}

// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if(GetTotalMassOfActorsOnPressurePlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();

	}
}

float UMoveDoor::GetTotalMassOfActorsOnPressurePlate()
{
	float TotalMass = 0.0f;

	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) { return TotalMass; }
	// Find all the overlapping actors
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for(const auto* Actor : OverlappingActors)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Actor %s standing on a pressure plate"), *Actor->GetName());
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();			// Mass is set in primitive component
	}

	return TotalMass;
}