// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AWeapon;

/**
 *  Actor Component for handling all functionality related to combat.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCombatComponent();

	friend class ABlasterCharacter; // friend class to allow full access to blaster character. Use only when necessary
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

	void EquipWeapon(AWeapon* WeaponToEquip);
	
protected:

	virtual void BeginPlay() override;

	/** Manage aiming down sights. To be called by Blaster Character. */
	void SetAiming(bool bIsAiming);

	/** Server RPC to set aiming from the client to the server. */
	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bIsAiming);
	
private:

	ABlasterCharacter* Character;

	/** The weapon that the character has currently equipped. */
	UPROPERTY(Replicated)
	AWeapon* EquippedWeapon;

	/** If the character is aiming or not. */
	UPROPERTY(Replicated)
	bool bAiming;
};