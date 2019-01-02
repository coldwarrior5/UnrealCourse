// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveDoor.h"
#include "GameFramework/Actor.h"

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

	auto Owner = GetOwner();
	const auto NewRotation = FRotator(0.0f, 70.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);

	
}


// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

