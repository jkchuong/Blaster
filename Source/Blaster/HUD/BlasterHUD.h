// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UTexture2D* CrosshairsCenter;

	UPROPERTY()
	UTexture2D* CrosshairsLeft;

	UPROPERTY()
	UTexture2D* CrosshairsRight;

	UPROPERTY()
	UTexture2D* CrosshairsTop;

	UPROPERTY()
	UTexture2D* CrosshairsBottom;
	
};

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()

public:

	// Draw the HUD every frame
	virtual void DrawHUD() override;

private:

	FHUDPackage HUDPackage;

public:

	FORCEINLINE void SetHudPackage(const FHUDPackage& Package) { HUDPackage = Package; }

};
