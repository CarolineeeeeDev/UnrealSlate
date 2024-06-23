// Lehan Li's Slate Learning Project

#include "Slate/SMyCompoundWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SBackgroundBlur.h"

#define LOCTEXT_NAMESPACE "MyNameSpace"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMyCompoundWidget::Construct(const FArguments& InArgs)
{
	MyOwnerHUD = InArgs._OwnerHUDArg;

	const FMargin ContentPadding = FMargin(500.0,300.0);
	const FMargin ButtonPadding = FMargin(20.0);
	const FText TitleText = LOCTEXT("SlateTest", "Slate Test");
	const FText PlayButtonText = LOCTEXT("PlayTest", "Play");
	const FText QuitButtonText = LOCTEXT("QuitTest", "Quit");
	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");//字体样式
	ButtonTextStyle.Size = 40.0f;
	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 40.0f;

	ChildSlot
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		.HAlign(HAlign_Fill).VAlign(VAlign_Fill)//布局方式
		[
			SNew(SImage)
			.ColorAndOpacity(FColor(1,0,0,0))
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SNew(SBackgroundBlur)
			.BlurStrength(10.0f)
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		.Padding(ContentPadding)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(TitleTextStyle)
				.Text(TitleText)
				.Justification(ETextJustify::Center)
			]
			+SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SMyCompoundWidget::OnPlayClick)
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(PlayButtonText)
					.Justification(ETextJustify::Center)
				]
			]
			+SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SMyCompoundWidget::OnQuitClick)
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(QuitButtonText)
					.Justification(ETextJustify::Center)
				]
			]
		]
	];
}

FReply SMyCompoundWidget::OnPlayClick() const
{
	if (MyOwnerHUD.IsValid())
	{
		MyOwnerHUD->RemoveMySlate();
	}
	return FReply::Handled();
}

FReply SMyCompoundWidget::OnQuitClick() const
{
	if (MyOwnerHUD.IsValid())
	{
		MyOwnerHUD->PlayerOwner->ConsoleCommand("quit");
	}
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE