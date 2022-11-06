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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	friend class ABlasterCharacter; // friend class to allow full access to blaster character. Use only when necessary

	void EquipWeapon(AWeapon* WeaponToEquip);
	
protected:

	virtual void BeginPlay() override;

private:

	ABlasterCharacter* Character;
	AWeapon* EquippedWeapon;
		
};
