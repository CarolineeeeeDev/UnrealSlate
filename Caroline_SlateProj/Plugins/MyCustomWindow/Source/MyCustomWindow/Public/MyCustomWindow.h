// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FMyCustomWindowModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	

private:
	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	void AddToolBarExtension(FToolBarBuilder& builder);
	void AddMenuBarExtension(FMenuBarBuilder& builder);
	void AddMenuExtension(FMenuBuilder& builder);

	TSharedRef<SDockTab> OnSpawnCustomWindow1(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<SDockTab> OnSpawnCustomWindow2(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<FTabManager> MyWindowTabManager;
	TSharedPtr<FTabManager::FLayout> MyWindowLayout;
};
