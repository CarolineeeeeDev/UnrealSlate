// Lehan Li's Slate Learning Project

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCanvas.h"

class MYCUSTOMWINDOW_API SMyCanvas : public SCanvas
{
public:
	SLATE_BEGIN_ARGS(SMyCanvas)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply OnClickButton();

	//ComboBox
	TSharedPtr<SComboBox<TSharedPtr<FString>>> MyComboBox;
	TSharedPtr<FString> CurrentItem = 0;
	TArray<TSharedPtr<FString>> Options;
	TSharedRef<SWidget> MakeWidgetForOption(TSharedPtr<FString> InOption);
	void OnSelectionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type);
	FText GetCurrentItemLabel() const;
};
