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
class UAnimMontage;

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

	/** Play the hip or ironsights firing montage. */
	void PlayFireMontage(bool bAiming);
	
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
	void FireButtonPressed();
	void FireButtonReleased();

	// For setting aim offset variables for the animation instance to call and blend aim poses.
	void AimOffset(float DeltaTime);

	// Override base jump so we can jump while crouching
	virtual void Jump() override;
	
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

	/**
	 * For checking if character should interp to aim offset yaw.
	 * I.e turning more than 90 degrees and need to rotate body.
	 */
	float InterpAimOffsetYaw;

	// Helper variables for setting AimOffset
	FRotator StartingAimRotation;

	/** State of the player when stationary. */
	ETurningInPlace TurningInPlace;

	/** Set the value of TurningInPlace according to yaw aim offset.*/
	void TurnInPlace(float DeltaTime);
	
	/** Animation Montage for for switching between hip and iron sight firing animations.*/
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* FireWeaponMontage;
	
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
