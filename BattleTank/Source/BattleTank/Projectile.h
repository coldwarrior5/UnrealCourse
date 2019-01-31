// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AProjectile();
	static float GetProjectileSpeed();
	void LaunchProjectile(float Speed) const;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	static AProjectile* Projectile;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileSpeed = 4000;
};
