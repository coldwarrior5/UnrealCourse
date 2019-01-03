// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerLocation;
	FRotator PlayerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotator);
	/*UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), 
		*PlayerLocation.ToString(), 
		*PlayerRotator.ToString()
	);*/
	FVector LineTraceEnd = PlayerLocation + PlayerRotator.Vector() * HandReach;
	DrawDebugLine(GetWorld(), PlayerLocation, LineTraceEnd, FColor(200,0,200), false, 0, 0, 2);
}

