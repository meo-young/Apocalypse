// Copyright Epic Games, Inc. All Rights Reserved.

#include "ApocalypseGameMode.h"
#include "ApocalypseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AApocalypseGameMode::AApocalypseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
