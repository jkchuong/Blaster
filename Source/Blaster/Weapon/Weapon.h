// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class USphereComponent;
class UWidgetComponent;
class UAnimationAsset;
class ACasing;

// Used for determining what we can do with the weapon in each state
UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial  UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped  UMETA(DisplayName = "Dropped"),

	EWS_MAX      UMETA(DisplayName = "DefaultMAX"),
};

/**
 *  Base weapon class for all weapons.
 *  Contains common functionality across all weapons such as pick up collision and pick up widgets.
 */
UCLASS()
class BLASTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// To be called when the sphere component is overlapped. Should only happen if it has authority role.
	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	// To be called when the sphere component ends overlap. Should only happen if it has authority role.
	UFUNCTION()
	virtual void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

private:	

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	USkeletalMeshComponent* WeaponMesh;

	/** The area for which a character can interact with the weapon when it is initialized. */
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	USphereComponent* AreaSphere;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	UWidgetComponent* PickupWidget;

	/** Current state of the weapon to determine how it behaves. Will be replicated. */
	UPROPERTY(ReplicatedUsing = OnRep_WeaponState, VisibleAnywhere, Category = "Weapon Properties")
	EWeaponState WeaponState;

	/** A Rep Notify. Will let the client know what to do when WeaponState value is changed and replicated. */
	UFUNCTION()
	void OnRep_WeaponState();

	/** The animation of the weapon being fired. */
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	UAnimationAsset* FireAnimation;

	/** The class of the ammo casing that will be ejected from the weapon when firing. */
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACasing> CasingClass;

public:

	void SetWeaponState(EWeaponState State);
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	/** Widget that is shown when overlapping with a character. */
	void ShowPickupWidget(bool bShowWidget);

	/** 
	 *	Fire the Weapon a direction and play any animations or effects required when firing.
	 *	@param HitTarget direction of the target that we want the projectile to move to.
	 */
	virtual void Fire(const FVector& HitTarget);

};
