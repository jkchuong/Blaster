// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterAnimInstance.h"

#include "BlasterCharacter.h"
#include "Blaster/Weapon/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());

}

void UBlasterAnimInstance::SetYawOffset(const float DeltaTime)
{
	// We want the difference between where we are looking and where we are moving so we know whether we are strafing or not
	const FRotator AimRotation = BlasterCharacter->GetBaseAimRotation();
	const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(BlasterCharacter->GetVelocity());
	const FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	
	// To allow interpolation directly from -180 to 180 and vice versa instead of -180 -> 0 -> 180
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.0f); 
	YawOffset = DeltaRotation.Yaw;
}

void UBlasterAnimInstance::SetLean(const float DeltaTime)
{
	// Lean is found by the difference in character rotation
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = BlasterCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);

	// For frame independence and since Delta will be a tiny value 
	const float Target = Delta.Yaw / DeltaTime;

	// Interpolated to remove jerkiness
	const float Interpolated = FMath::FInterpTo(Lean, Target, DeltaTime, 6.0f);

	// Clamped in case player moves the mouse very quickly
	Lean = FMath::Clamp(Interpolated, -90.0f, 90.0f);
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!BlasterCharacter)
	{
		BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
	}

	// Checking again since this function could be running before pawn owner has been set, i.e in the editor
	if (!BlasterCharacter)
	{
		return;
	}

	// Set values for animation blueprint
	FVector Velocity = BlasterCharacter->GetVelocity();
	Velocity.Z = 0.0f;
	Speed = Velocity.Size();
	
	bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0;
	bWeaponEquipped = BlasterCharacter->IsWeaponEquipped();
	EquippedWeapon = BlasterCharacter->GetEquippedWeapon();
	bIsCrouched = BlasterCharacter->bIsCrouched;
	bAiming = BlasterCharacter->IsAiming();
	TurningInPlace = BlasterCharacter->GetTurningInPlace();
	AimOffsetYaw = BlasterCharacter->GetAimOffsetYaw();
	AimOffsetPitch = BlasterCharacter->GetAimOffsetPitch();

	SetYawOffset(DeltaTime);
	SetLean(DeltaTime);

	// Update the left hand position only if weapon mesh and character mesh are valid	
	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && BlasterCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), RTS_World);

		// Apply left hand transform relative to hand_r position so the positions stays relative however animation moves
		FVector OutPosition;
		FRotator OutRotation;
		BlasterCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(),
		                                                  FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));

		
	}

}