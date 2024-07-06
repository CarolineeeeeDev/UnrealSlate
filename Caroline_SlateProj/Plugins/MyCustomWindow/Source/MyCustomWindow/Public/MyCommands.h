// Lehan Li's Slate Learning Project

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Styling/SlateStyle.h"

class MYCUSTOMWINDOW_API FMyCommands : public TCommands<FMyCommands>
{
public:
	FMyCommands() : 
		TCommands<FMyCommands>(TEXT("MyMenu"), NSLOCTEXT("Contexts","MyMenu", "My Menu test"), NAME_None, FMyCommands::GetStyleSetName())
	{

	}
	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> FileCommand;
	TSharedPtr<FUICommandInfo> EditCommand;
	TSharedPtr<FUICommandInfo> WindowCommand;

	
};
