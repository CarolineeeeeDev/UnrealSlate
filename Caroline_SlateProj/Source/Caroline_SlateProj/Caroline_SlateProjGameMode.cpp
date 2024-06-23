// Copyright Epic Games, Inc. All Rights Reserved.

#include "Caroline_SlateProjGameMode.h"
#include "Caroline_SlateProjCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACaroline_SlateProjGameMode::ACaroline_SlateProjGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
