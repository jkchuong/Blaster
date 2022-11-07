// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnRight(float Value);
	void LookUp(float Value);
	void EquipButtonPressed();

private:

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	AWeapon* OverlappingWeapon;

	// A Rep Notify, called whenever Overlapping Weapon gets replicated
	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UPROPERTY(VisibleAnywhere)
	UCombatComponent* CombatComponent;

	// To be called on the client and executed on the server - Server Remote Procedure Call (RPC)
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();
	
public:

	/**
	 *  For setting whether the character is overlapping a weapon.
	 *  Will be called by the Weapon class but only on authority server.
	 */
	void SetOverlappingWeapon(AWeapon* Weapon);
};
