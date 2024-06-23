// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MyCustomWindowStyle.h"

class FMyCustomWindowCommands : public TCommands<FMyCustomWindowCommands>
{
public:

	FMyCustomWindowCommands()
		: TCommands<FMyCustomWindowCommands>(TEXT("MyCustomWindow"), NSLOCTEXT("Contexts", "MyCustomWindow", "MyCustomWindow Plugin"), NAME_None, FMyCustomWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};