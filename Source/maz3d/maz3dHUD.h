// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "maz3dHUD.generated.h"

UCLASS()
class Amaz3dHUD : public AHUD
{
	GENERATED_BODY()

public:
	Amaz3dHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

