// Lehan Li's Slate Learning Project

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class MYCUSTOMWINDOW_API SMyLevelEditorWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyLevelEditorWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	TSharedRef<SDockTab> SpawnCustomTab1(const FSpawnTabArgs& Arg);
	TSharedRef<SDockTab> SpawnCustomTab2(const FSpawnTabArgs& Arg);
	TSharedRef<SDockTab> SpawnCustomTab3(const FSpawnTabArgs& Arg);
	TSharedRef<SDockTab> SpawnCustomTab4(const FSpawnTabArgs& Arg);
	TSharedRef<SDockTab> SpawnCustomTab5(const FSpawnTabArgs& Arg);
	TSharedRef<SDockTab> SpawnCustomTab6(const FSpawnTabArgs& Arg);
	TSharedRef<SDockTab> SpawnCustomTab7(const FSpawnTabArgs& Arg);
};
