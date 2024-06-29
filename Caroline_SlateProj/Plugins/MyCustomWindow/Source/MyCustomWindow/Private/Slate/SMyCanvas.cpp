// Lehan Li's Slate Learning Project


#include "Slate/SMyCanvas.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMyCanvas::Construct(const FArguments& InArgs)
{
	AddSlot()
		.Position(FVector2D(100, 100))
		.Size(FVector2D(100, 40))
		[
			SNew(SButton)
				.OnClicked(this, &SMyCanvas::OnClickButton)
		];
	AddSlot()
		.Position(FVector2D(300, 100))
		.Size(FVector2D(100, 40))
		[
			SNew(SButton)
				.OnClicked(this, &SMyCanvas::OnClickButton)
		];
	//ComboBox
	Options.Add(MakeShareable(new FString("One")));
	Options.Add(MakeShareable(new FString("Two")));
	Options.Add(MakeShareable(new FString("Three")));
	AddSlot()
		.Position(FVector2D(500, 100))
		.Size(FVector2D(100, 40))
		[
			SAssignNew(MyComboBox, SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&Options)
				.OnGenerateWidget(this,&SMyCanvas::MakeWidgetForOption)
				.OnSelectionChanged(this,&SMyCanvas::OnSelectionChanged)
				.InitiallySelectedItem(CurrentItem)
				[
					SNew(STextBlock)
						.Text(this,&SMyCanvas::GetCurrentItemLabel)
				]
		];
}
FReply SMyCanvas::OnClickButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Button Clicked"));
	return FReply::Handled();
}
TSharedRef<SWidget> SMyCanvas::MakeWidgetForOption(TSharedPtr<FString> InOption)
{

	return SNew(STextBlock).Text(FText::FromString(*InOption));
}
void SMyCanvas::OnSelectionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type)
{
	CurrentItem = NewValue;
}
FText SMyCanvas::GetCurrentItemLabel() const
{
	if (CurrentItem.IsValid())
	{
		return FText::FromString(*CurrentItem);
	}
	return FText::FromString("Failed");
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
