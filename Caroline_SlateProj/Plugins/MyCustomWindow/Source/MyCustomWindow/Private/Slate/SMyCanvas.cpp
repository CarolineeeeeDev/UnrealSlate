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

	//HorizontalBox and VerticalBox
	AddSlot()
		.Position(FVector2D(100, 300))
		.Size(FVector2D(100, 40))
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(2.0)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
				]
		];
	AddSlot()
		.Position(FVector2D(300, 300))
		.Size(FVector2D(100, 40))
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				[
					SNew(SButton)
				]
				+ SVerticalBox::Slot()
				.FillHeight(2.0)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
				]
				+ SVerticalBox::Slot()
				[
					SNew(SButton)
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
