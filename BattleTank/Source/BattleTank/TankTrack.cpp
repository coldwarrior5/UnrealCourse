// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce() const
{
	const auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(),GetRightVector());
	const auto DeltaTime = GetWorld()->GetDeltaSeconds();
	const auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	const auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;		// We divide by two because we have two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack() const
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Throttle: %f"), *GetName(), CurrentThrottle)
	const auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	const auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}
