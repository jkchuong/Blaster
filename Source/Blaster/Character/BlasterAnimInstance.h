// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BlasterAnimInstance.generated.h"

class ABlasterCharacter;

/**
 *  Class to handle the animations for the Blaster Character
 */
UCLASS()
class BLASTER_API UBlasterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	/** NativeInitializeAnimation is basically the same as begin play */
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:

	/** The Blaster Character that this animation instance will be attached to. */
	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	ABlasterCharacter* BlasterCharacter;

	/** The speed of the Blaster Character. Used to determine running or walking animation. */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	/** Whether the Blaster Character is in the air or not. Set with Character class. */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	/** Whether the Blaster Character is accelerating or not. Set with Character class. */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;

	/** Whether the Blaster Character is equipping a weapon or not. Set with the Combat Component. */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bWeaponEquipped;

	/** Whether the Blaster Character is crouching or not. Set with the Character class. */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsCrouched;
	
	/** Whether the Blaster Character is aiming down sights or not. Set with the Combat Component. */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bAiming;

	/**
	 *  The amount the Blaster Character is strafing left or right or moving backwards from -180 to 180.
	 *  Negative value means strafing left, positive value means strafing right.
	 */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float YawOffset;

	/**
	 *  The amount the Blaster Character is leaning left or right when the player rotates their camera.
	 *  Negative value means leaning left, positive value means leaning right.
	 */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Lean;

	void SetYawOffset(float DeltaTime);
	void SetLean(float DeltaTime);

	// Helper variables for settings Lean and YawOffset
	FRotator CharacterRotationLastFrame;
	FRotator CharacterRotation;
	FRotator DeltaRotation;

	/** Yaw Aim Offset when a weapon is equipped. Will be used to drive how high or low the Blaster Character will look. */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float AimOffsetYaw;

	/** Pitch Aim Offset when a weapon is equipped. Will be used to drive how left or right the Blaster Character will look. */
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float AimOffsetPitch;
};
