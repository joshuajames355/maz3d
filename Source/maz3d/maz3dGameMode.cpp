// Copyright Epic Games, Inc. All Rights Reserved.

#include "maz3dGameMode.h"
#include "maz3dHUD.h"
#include "maz3dCharacter.h"
#include "UObject/ConstructorHelpers.h"

Amaz3dGameMode::Amaz3dGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Amaz3dHUD::StaticClass();
}
