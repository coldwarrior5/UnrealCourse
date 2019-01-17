// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include <string>

void UTankBarrel::Elevate(float Degrees)
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	UE_LOG(LogTemp, Warning, TEXT("%s needs to elevate barrel for %f"), *GetOwner()->GetName(), Degrees);
}
