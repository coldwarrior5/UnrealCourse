// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "MoveDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UMoveDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveDoor();
	void OpenDoor() const;
	void CloseDoor() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	float GetTotalMassOfActorsOnPressurePlate();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* OwningDoor;
	UPROPERTY(EditAnywhere)
		float OpenAngle = 90.0f;
	UPROPERTY(VisibleAnywhere)
		float ClosedAngle = 0.0f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate{};
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.5f;
	float LastDoorOpenTime;
	UPROPERTY(EditAnywhere)
		float TriggerMass = 50.0f;
};
