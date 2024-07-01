// Lehan Li's Slate Learning Project


#include "Slate/SMyCanvas.h"
#include "SlateOptMacros.h"
#include "Slate/MySlateWidgetMainStyle.h"
#include "MyCustomWindowStyle.h"
#include "Misc/MessageDialog.h"

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
	//SEditableText
	AddSlot()
		.Position(FVector2D(500, 300))
		.Size(FVector2D(200, 60))
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SEditableText)
						.Justification(ETextJustify::Left)
						.HintText(FText::FromString("Input1"))
						.Font(FCoreStyle::Get().GetFontStyle("Embossedtext"))
						.ToolTipText(FText::FromString("MyEditableText"))
						.ColorAndOpacity(FSlateColor::UseForeground())
				]
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SEditableText)
						.Justification(ETextJustify::Left)
						.HintText(FText::FromString("Input2"))
						.Font(FCoreStyle::Get().GetFontStyle("Embossedtext"))
						.ToolTipText(FText::FromString("MyEditableText"))
						.ColorAndOpacity(FSlateColor::UseForeground())
				]
		];
	//SSplitter
	AddSlot()
		.Position(FVector2D(50, 400))
		.Size(FVector2D(200, 200))
		[
			SNew(SSplitter)
				+SSplitter::Slot()
				[
					SNew(SButton)
						[
							SNew(STextBlock)
								.Text(FText::FromString("Button1"))
						]
				]
				+ SSplitter::Slot()
				[
					SNew(SButton)
						.Text(FText::FromString("Button2"))
				]
		];
	//StyleImage
	const struct FMainWidgetStyle* MyCustomWidgetStyle = &FMyCustomWindowStyle::Get().GetWidgetStyle<FMainWidgetStyle>(TEXT("MyWidgetStyle"));
	AddSlot()
		.Position(FVector2D(300, 400))
		.Size(FVector2D(100, 100))
		[
			SNew(SImage)
				.Image(&MyCustomWidgetStyle->MyBrush)
		];
	//
	AddSlot()
		.Position(FVector2D(500, 400))
		.Size(FVector2D(100, 100))
		[
			SNew(SOverlay)
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
						.Image(&MyCustomWidgetStyle->MyBrush)
				]
				//+SOverlay::Slot()
				//.HAlign(HAlign_Center)
				//.VAlign(VAlign_Center)
				//[
				//	SNew(SImage)
				//		.Image(&MyCustomWidgetStyle->MyBrush)
				//]
		];
	AddSlot()
		.Position(FVector2D(700, 400))
		.Size(FVector2D(200, 200))
		[
			SNew(STextBlock)
				.Text(FText::FromString("MyCustomTextBlock"))
				.Justification(ETextJustify::Left)
				.Font(MyCustomWidgetStyle->MyFont)
				.ColorAndOpacity(MyCustomWidgetStyle->MyColor)
				.AutoWrapText(true)
		];
	AddSlot()
		.Position(FVector2D(700, 500))
		.Size(FVector2D(100, 100))
		[
			SNew(SOverlay)
				+SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				[
					SNew(SBox)
						.WidthOverride(50)
						.HeightOverride(50)
						[
							SNew(SBorder)
								.BorderImage(&MyCustomWidgetStyle->MyBrush)
						]
				]
		];
	AddSlot()
		.Position(FVector2D(100, 700))
		.Size(FVector2D(100, 50))
		[
			SNew(SButton)
				.Text(FText::FromString("MyTestButton"))
				.OnHovered_Lambda([]() {UE_LOG(LogTemp, Warning, TEXT("OnHorvered"))})
				.OnPressed_Lambda([]() {UE_LOG(LogTemp, Warning, TEXT("OnPressed"))})
				.OnReleased_Lambda([]() {UE_LOG(LogTemp, Warning, TEXT("OnReleased"))})
		];
}

FReply SMyCanvas::OnClickButton()
{
	FMessageDialog::Open(EAppMsgType::OkCancel, FText::FromString("Button is OKCancel"));
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
