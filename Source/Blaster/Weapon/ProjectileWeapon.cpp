// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"

void AProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	// Only want to spawn the projectile in server to prevent cheating from client side
	if (!HasAuthority())
	{
		return;
	}

	// So we know who fired the weapon
	APawn* InstigatorPawn = Cast<APawn>(GetOwner());

	if (const USkeletalMeshSocket* MuzzleSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash")))
	{
		// Where the projectile will spawn. Makes most sense to have it come from the muzzle
		FTransform SocketTransform = MuzzleSocket->GetSocketTransform(GetWeaponMesh());

		// Direction the projectile will move. Does not follow the barrel, but where the player aims with
		// TraceUnderCrosshairs as it's hard to get the barrel aiming exactly where the player is pointing.
		FVector ToTarget = HitTarget - SocketTransform.GetLocation();
		FRotator TargetRotation = ToTarget.Rotation();
		
		if (ProjectileClass && InstigatorPawn)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = GetOwner();
			SpawnParameters.Instigator = InstigatorPawn;
			
			if (UWorld* World = GetWorld())
			{
				World->SpawnActor<AProjectile>(
					ProjectileClass,
					SocketTransform.GetLocation(),
					TargetRotation,
					SpawnParameters
				);
			}
		}
	}
}
