#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerLocation;
	FRotator PlayerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotator);
	const FVector LineTraceEnd = PlayerLocation + PlayerRotator.Vector() * HandReach;

	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

/// Look for attached Physics handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component!"), *GetOwner()->GetName())
	}
}

/// Look for attached Physics handle
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found"))
		
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component!"), *GetOwner()->GetName())
	}
}

// Ray-cast and grab what is within reach
void UGrabber::Grab()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	const auto ComponentToGrab = HitResult.GetComponent();
	const auto ActorHit = HitResult.GetActor();
	if(ActorHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			HitResult.ImpactPoint,
			ComponentToGrab->GetComponentRotation()
			);
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerLocation;
	FRotator PlayerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotator);
	const FVector LineTraceEnd = PlayerLocation + PlayerRotator.Vector() * HandReach;

	/*
	 * //Draw a line in the world to visualize
	 * DrawDebugLine(GetWorld(), PlayerLocation, LineTraceEnd, FColor(200, 0, 200), false, 0, 0, 2);
	 */

	 /// Setup query parameters
	const FCollisionQueryParams CollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	/// Line-trace (AKA ray-cast) out to reach distance
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		CollisionQueryParams
	);
	return Hit;
}
