// Lehan Li's Slate Learning Project


#include "SMyLevelEditorWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMyLevelEditorWidget::Construct(const FArguments& InArgs)
{
	FGlobalTabmanager::Get()->UnregisterAllTabSpawners();
	FGlobalTabmanager::Get()->RegisterTabSpawner("3DView", FOnSpawnTab::CreateRaw(this, &SMyLevelEditorWidget::SpawnCustomTab1));
	FGlobalTabmanager::Get()->RegisterTabSpawner("PlaceActors", FOnSpawnTab::CreateRaw(this, &SMyLevelEditorWidget::SpawnCustomTab2));
	FGlobalTabmanager::Get()->RegisterTabSpawner("OutLine", FOnSpawnTab::CreateRaw(this, &SMyLevelEditorWidget::SpawnCustomTab3));
	FGlobalTabmanager::Get()->RegisterTabSpawner("Levels", FOnSpawnTab::CreateRaw(this, &SMyLevelEditorWidget::SpawnCustomTab4));
	FGlobalTabmanager::Get()->RegisterTabSpawner("Detail", FOnSpawnTab::CreateRaw(this, &SMyLevelEditorWidget::SpawnCustomTab5));
	FGlobalTabmanager::Get()->RegisterTabSpawner("WorldSetting", FOnSpawnTab::CreateRaw(this, &SMyLevelEditorWidget::SpawnCustomTab6));
	FGlobalTabmanager::Get()->RegisterTabSpawner("ContentBrowser",FOnSpawnTab::CreateRaw(this, &SMyLevelEditorWidget::SpawnCustomTab7));
	
	TSharedRef<FTabManager::FLayout> LayOut = FTabManager::NewLayout(TEXT("LayOut"))
		->AddArea(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewSplitter()
				->SetSizeCoefficient(0.86)
				->SetOrientation(Orient_Horizontal)
				->Split(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.32)
					->AddTab("ContentBrowser", ETabState::OpenedTab)
					->AddTab("PlaceActors", ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.56)
					->SetHideTabWell(false)
					->AddTab("3DView", ETabState::OpenedTab)
				)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetSizeCoefficient(0.14)
				->SetOrientation(Orient_Vertical)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.4)
					->SetHideTabWell(true)
					->AddTab("OutLine", ETabState::OpenedTab)
					->AddTab("Levels", ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.6)
					->SetHideTabWell(true)
					->AddTab("Detail", ETabState::OpenedTab)
					->AddTab("WorldSetting", ETabState::OpenedTab)
				)
			)
		);
	TSharedRef<SWidget> LevelEditorContent = FGlobalTabmanager::Get()->RestoreFrom(LayOut, TSharedPtr<SWindow>()).ToSharedRef();
	ChildSlot[
		SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				LevelEditorContent
			]
	];
}
TSharedRef<SDockTab> SMyLevelEditorWidget::SpawnCustomTab1(const FSpawnTabArgs& Arg)
{
	return SNew(SDockTab);
}
TSharedRef<SDockTab> SMyLevelEditorWidget::SpawnCustomTab2(const FSpawnTabArgs& Arg)
{
	return SNew(SDockTab);
}
TSharedRef<SDockTab> SMyLevelEditorWidget::SpawnCustomTab3(const FSpawnTabArgs& Arg)
{
	return SNew(SDockTab);
}
TSharedRef<SDockTab> SMyLevelEditorWidget::SpawnCustomTab4(const FSpawnTabArgs& Arg)
{
	return SNew(SDockTab);
}
TSharedRef<SDockTab> SMyLevelEditorWidget::SpawnCustomTab5(const FSpawnTabArgs& Arg)
{
	return SNew(SDockTab);
}
TSharedRef<SDockTab> SMyLevelEditorWidget::SpawnCustomTab6(const FSpawnTabArgs& Arg)
{
	return SNew(SDockTab);
}
TSharedRef<SDockTab> SMyLevelEditorWidget::SpawnCustomTab7(const FSpawnTabArgs& Arg)
{
	return SNew(SDockTab);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
