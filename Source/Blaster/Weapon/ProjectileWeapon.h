// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "ProjectileWeapon.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS()
class BLASTER_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

public:

	/** Fire the weapon. */
	virtual void Fire(const FVector& HitTarget) override;

private:

	/** Projectile class that the weapon will shoot when fired. */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;

	
};
