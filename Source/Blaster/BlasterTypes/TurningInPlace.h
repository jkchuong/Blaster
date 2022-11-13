#pragma once

/**
 *  For letting character know what it's doing if idle.
 *  Used if the character turns more than 90 degrees either way so they can turn their whole body to face another direction.
 */
UENUM(BlueprintType)
enum class ETurningInPlace : uint8
{
	ETIP_Left		 UMETA(Display = "Turning Left"),	
	ETIP_Right		 UMETA(Display = "Turning Right"),	
	ETIP_NotTurning  UMETA(Display = "Not Turning"),
	ETIP_MAX         UMETA(Display = "DefaultMAX")
};
