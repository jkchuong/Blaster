// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "GameFramework/Character.h"
#include "BlasterCharacter.generated.h"

class USpringArmComponent;
class AWeapon;
class UCombatComponent;
class UCameraComponent;
class UWidgetComponent;

/**
 *  Class for defining a playable character in the game.
 */
UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABlasterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** 
	 *  For registering variables that are marked with UPROPERTY(Replicated) to be replicated.
	 *  Only updates when value is changed, not every frame.
	 */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Components will be constructed by the time this is called
	virtual void PostInitializeComponents() override;
	
protected:

	virtual void BeginPlay() override;

	// Player input functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnRight(float Value);
	void LookUp(float Value);
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();

	// For setting aim offset variables for the animation instance to call and blend aim poses.
	void AimOffset(float DeltaTime);
	
private:

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget;

	// The weapon the character is currently overlapping. Only changes on the server and replicated with a rep notify.
	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	AWeapon* OverlappingWeapon;

	// A Rep Notify for handling OverlappingWeapon from server
	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UPROPERTY(VisibleAnywhere)
	UCombatComponent* CombatComponent;

	// To be called on the client and executed on the server - Server Remote Procedure Call (RPC)
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	// Offsets when aiming with a weapon.
	float AimOffsetYaw;
	float AimOffsetPitch;

	// Helper variables for setting AimOffset
	FRotator StartingAimRotation;

	/** State of the player when stationary. */
	ETurningInPlace TurningInPlace;

	/** Set the value of TurningInPlace according to yaw aim offset.*/
	void TurnInPlace(float DeltaTime);
	
public:

	/**
	 *  For setting whether the character is overlapping a weapon.
	 *  Will be called by the Weapon class but only on authority server.
	 */
	void SetOverlappingWeapon(AWeapon* Weapon);

	/** Checks whether a weapon is equipped or not. */
	bool IsWeaponEquipped();

	/** Checks whether character is aiming down sights or not. */
	bool IsAiming();

	/** Get the aim offset created when facing a direction with a weapon. */
	FORCEINLINE float GetAimOffsetYaw() const { return AimOffsetYaw; }
	FORCEINLINE float GetAimOffsetPitch() const { return AimOffsetPitch; }

	AWeapon* GetEquippedWeapon();
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	
};
