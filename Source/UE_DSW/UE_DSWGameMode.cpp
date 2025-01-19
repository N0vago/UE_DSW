// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_DSWGameMode.h"
#include "UE_DSWCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE_DSWGameMode::AUE_DSWGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
