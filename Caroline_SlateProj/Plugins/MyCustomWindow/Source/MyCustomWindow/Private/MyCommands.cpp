// Lehan Li's Slate Learning Project


#include "MyCommands.h"

#define LOCTEXT_NAMESPACE "FMyCustomWindowModule"

void FMyCommands::RegisterCommands()
{
	UI_COMMAND(FileCommand, "MyFile", "It is File Operate", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::O));
	UI_COMMAND(EditCommand, "MyEdit", "It is Edit Operate", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Q));
	UI_COMMAND(WindowCommand, "MyWindow", "It is Window Operate", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::E));
}

#undef LOCTEXT_NAMESPACE
