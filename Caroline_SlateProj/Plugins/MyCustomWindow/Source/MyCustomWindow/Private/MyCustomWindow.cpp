// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCustomWindow.h"
#include "MyCustomWindowStyle.h"
#include "MyCustomWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName MyCustomWindowTabName("MyCustomWindow");

#define LOCTEXT_NAMESPACE "FMyCustomWindowModule"

void FMyCustomWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMyCustomWindowStyle::Initialize();
	FMyCustomWindowStyle::ReloadTextures();

	FMyCustomWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMyCustomWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMyCustomWindowModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMyCustomWindowModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyCustomWindowTabName, FOnSpawnTab::CreateRaw(this, &FMyCustomWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMyCustomWindowTabTitle", "MyCustomWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	//工具栏扩展按钮
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtender> ToolBarExtender = MakeShareable(new FExtender);
	ToolBarExtender->AddToolBarExtension(
		"Play",
		EExtensionHook::After,
		PluginCommands,
		FToolBarExtensionDelegate::CreateRaw(this, &FMyCustomWindowModule::AddToolBarExtension)
	);
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolBarExtender);
	
	TSharedPtr<FExtender> MenuBarExtender = MakeShareable(new FExtender);
	MenuBarExtender->AddMenuBarExtension("Help", EExtensionHook::After, PluginCommands, FMenuBarExtensionDelegate::CreateRaw(this, &FMyCustomWindowModule::AddMenuBarExtension));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuBarExtender);

}

void FMyCustomWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMyCustomWindowStyle::Shutdown();

	FMyCustomWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MyCustomWindowTabName);
}

TSharedRef<SDockTab> FMyCustomWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FMyCustomWindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("MyCustomWindow.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FMyCustomWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MyCustomWindowTabName);
}

void FMyCustomWindowModule::AddToolBarExtension(FToolBarBuilder& builder)
{
	builder.AddToolBarButton(FMyCustomWindowCommands::Get().OpenPluginWindow);
}

void FMyCustomWindowModule::AddMenuBarExtension(FMenuBarBuilder& builder)
{
	builder.AddMenuEntry(FMyCustomWindowCommands::Get().OpenPluginWindow);
}

void FMyCustomWindowModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMyCustomWindowCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMyCustomWindowCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyCustomWindowModule, MyCustomWindow)