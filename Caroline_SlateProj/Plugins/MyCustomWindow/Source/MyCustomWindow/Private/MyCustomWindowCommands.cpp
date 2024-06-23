// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCustomWindowCommands.h"

#define LOCTEXT_NAMESPACE "FMyCustomWindowModule"

void FMyCustomWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MyCustomWindow", "Bring up MyCustomWindow window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
