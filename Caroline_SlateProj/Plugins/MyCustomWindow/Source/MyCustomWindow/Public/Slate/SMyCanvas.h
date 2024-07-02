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

	TArray<TSharedPtr<SCheckBox>> MyCheckBoxArray;
	template<int32 T>
	void MyOnCheckBoxStateChange(ECheckBoxState emstate)
	{
		if (MyCheckBoxArray.IsValidIndex(T))
		{
			for (int32 i = 0; i < MyCheckBoxArray.Num(); i++)
			{
				if (i == T)
				{
					if (MyCheckBoxArray[i].IsValid() || MyCheckBoxArray[i].Get())
					{
						MyCheckBoxArray[i]->SetIsChecked(emstate);
					}
				}
				else
				{
					if (MyCheckBoxArray[i].IsValid() || MyCheckBoxArray[i].Get())
					{
						MyCheckBoxArray[i]->SetIsChecked(ECheckBoxState::Unchecked);
					}
				}
			}
		}
	}
};
