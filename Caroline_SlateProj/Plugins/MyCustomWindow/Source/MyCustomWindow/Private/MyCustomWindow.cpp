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
static const FName MyWindowTabName1("MyWindow1");
static const FName MyWindowTabName2("MyWindow2");

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
	
	//自定义窗口
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyCustomWindowTabName, FOnSpawnTab::CreateRaw(this, &FMyCustomWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMyCustomWindowTabTitle", "MyCustomWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyWindowTabName1, FOnSpawnTab::CreateRaw(this, &FMyCustomWindowModule::OnSpawnCustomWindow1))
		.SetDisplayName(LOCTEXT("FMyWindowTitle1", "MyWindow1"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyWindowTabName2, FOnSpawnTab::CreateRaw(this, &FMyCustomWindowModule::OnSpawnCustomWindow2))
		.SetDisplayName(LOCTEXT("FMyWindowTitle2", "MyWindow2"))
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
	//主菜单栏扩展按钮
	TSharedPtr<FExtender> MenuBarExtender = MakeShareable(new FExtender);
	MenuBarExtender->AddMenuBarExtension("Help", EExtensionHook::After, PluginCommands, FMenuBarExtensionDelegate::CreateRaw(this, &FMyCustomWindowModule::AddMenuBarExtension));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuBarExtender);
	//菜单栏扩展按钮
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
	MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::Before, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMyCustomWindowModule::AddMenuExtension));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
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
	//FText WidgetText = FText::Format(
	//	LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
	//	FText::FromString(TEXT("FMyCustomWindowModule::OnSpawnPluginTab")),
	//	FText::FromString(TEXT("MyCustomWindow.cpp"))
	//	);

	//return SNew(SDockTab)
	//	.TabRole(ETabRole::NomadTab)
	//	[
	//		// Put your tab content here!
	//		SNew(SBox)
	//		.HAlign(HAlign_Center)
	//		.VAlign(VAlign_Center)
	//		[
	//			SNew(STextBlock)
	//			.Text(WidgetText)
	//		]
	//	];
	const TSharedRef<SDockTab> NomadTab = SNew(SDockTab).TabRole(ETabRole::NomadTab);
	if (!MyWindowTabManager.IsValid())
	{
		MyWindowTabManager = FGlobalTabmanager::Get()->NewTabManager(NomadTab);
		MyWindowLayout = FTabManager::NewLayout("MyLayout")
			->AddArea
			(
				FTabManager::NewPrimaryArea()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.5f)
					->AddTab(MyWindowTabName1, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.5f)
					->AddTab(MyWindowTabName2, ETabState::OpenedTab)
				)
			);
	}

	TSharedRef<SWidget> TabContent = MyWindowTabManager->RestoreFrom(MyWindowLayout.ToSharedRef(), TSharedPtr<SWindow>()).ToSharedRef();
	NomadTab->SetContent(TabContent);
	return NomadTab;
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

void FMyCustomWindowModule::AddMenuExtension(FMenuBuilder& builder)
{
	builder.AddMenuEntry(FMyCustomWindowCommands::Get().OpenPluginWindow);
}

TSharedRef<SDockTab> FMyCustomWindowModule::OnSpawnCustomWindow1(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab);
}

TSharedRef<SDockTab> FMyCustomWindowModule::OnSpawnCustomWindow2(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab);
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