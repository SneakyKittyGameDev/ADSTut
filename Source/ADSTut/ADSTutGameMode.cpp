// Copyright Epic Games, Inc. All Rights Reserved.

#include "ADSTutGameMode.h"
#include "ADSTutHUD.h"
#include "ADSTutCharacter.h"
#include "UObject/ConstructorHelpers.h"

AADSTutGameMode::AADSTutGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	//HUDClass = AADSTutHUD::StaticClass();
}
