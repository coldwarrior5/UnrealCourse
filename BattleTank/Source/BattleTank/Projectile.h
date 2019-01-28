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
	static float GetProjectileSpeed() 
	{
		// TODO Create instance and return the value of the projectile speed
		//AProjectile TempProjectile{};		// This is how we create an instance of a class
		//const auto ProjectileSpeed = TempProjectile.ProjectileSpeed;
		//TempProjectile.Destroy();
		return 4000;
	};
	void LaunchProjectile(float Speed) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileSpeed = 4000;

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
};
