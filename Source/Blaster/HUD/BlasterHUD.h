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

	UPROPERTY()
	UTexture2D* CrosshairsCenter = nullptr;

	UPROPERTY()
	UTexture2D* CrosshairsLeft = nullptr;

	UPROPERTY()
	UTexture2D* CrosshairsRight = nullptr;

	UPROPERTY()
	UTexture2D* CrosshairsTop = nullptr;

	UPROPERTY()
	UTexture2D* CrosshairsBottom = nullptr;
	
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

	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter);
	
public:

	FORCEINLINE void SetHudPackage(const FHUDPackage& Package) { HUDPackage = Package; }

};
