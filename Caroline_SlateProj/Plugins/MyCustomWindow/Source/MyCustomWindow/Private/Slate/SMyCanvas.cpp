// Lehan Li's Slate Learning Project


#include "Slate/SMyCanvas.h"
#include "SlateOptMacros.h"
#include "Slate/MySlateWidgetMainStyle.h"
#include "MyCustomWindowStyle.h"
#include "Misc/MessageDialog.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Text/SMultiLineEditableText.h"
#include "Widgets/Layout/SWrapBox.h"

#define LOCTEXT_NAMESPACE "MyNameSpace"

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
	//SConstraintCanvas
	AddSlot()
		.Position(FVector2D(300, 700))
		.Size(FVector2D(100, 100))
		[
			SNew(SConstraintCanvas)
				+SConstraintCanvas::Slot()
				.Anchors(0.f)
				.Offset(FMargin(0, 0, 100, 30))
				.Alignment(FVector2D(0,0))
				.AutoSize(false)
				.ZOrder(0)
				[
					SNew(STextBlock)
						.Text(FText::FromString("MyText1"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SConstraintCanvas::Slot()
				.Anchors(0.f)
				.Offset(FMargin(0, 30, 100, 30))
				.Alignment(FVector2D(0, 0))
				.AutoSize(false)
				.ZOrder(0)
				[
					SNew(STextBlock)
						.Text(FText::FromString("MyText2"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SConstraintCanvas::Slot()
				.Anchors(0.f)
				.Offset(FMargin(0, 60, 100, 30))
				.Alignment(FVector2D(0, 0))
				.AutoSize(false)
				.ZOrder(0)
				[
					SNew(STextBlock)
						.Text(FText::FromString("MyText3"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
		];
	MyCheckBoxArray.SetNum(3);
	AddSlot()
		.Position(FVector2D(500, 700))
		.Size(FVector2D(100, 100))
		[
			SNew(SVerticalBox)
				+SVerticalBox::Slot()
				[
					SAssignNew(MyCheckBoxArray[0], SCheckBox)
						.IsEnabled(true)
						.IsChecked(ECheckBoxState::Unchecked)
						.OnCheckStateChanged(this, &SMyCanvas::MyOnCheckBoxStateChange<0>)
						.Content()
						[
							SNew(STextBlock)
								.Text(FText::FromString("MyCheckBox1"))
						]
				]
				+ SVerticalBox::Slot()
				[
					SAssignNew(MyCheckBoxArray[1], SCheckBox)
						.IsEnabled(true)
						.IsChecked(ECheckBoxState::Unchecked)
						.OnCheckStateChanged(this, &SMyCanvas::MyOnCheckBoxStateChange<1>)
						.Content()
						[
							SNew(STextBlock)
								.Text(FText::FromString("MyCheckBox2"))
						]
				]
				+ SVerticalBox::Slot()
				[
					SAssignNew(MyCheckBoxArray[2], SCheckBox)
						.IsEnabled(true)
						.IsChecked(ECheckBoxState::Unchecked)
						.OnCheckStateChanged(this, &SMyCanvas::MyOnCheckBoxStateChange<2>)
						.Content()
						[
							SNew(STextBlock)
								.Text(FText::FromString("MyCheckBox3"))
						]
				]
		];
	//SGridPanel
	AddSlot()
		.Position(FVector2D(700, 650))
		.Size(FVector2D(200, 200))
		[
			SNew(SGridPanel)
				.FillColumn(0, 1)
				.FillColumn(1, 1)
				.FillRow(0, 1)
				.FillRow(1, 1)
				+SGridPanel::Slot(0,0)
				[
					SNew(SImage)
						.Image(&MyCustomWidgetStyle->MyBrush)
				]
				+ SGridPanel::Slot(0, 1)
				[
					SNew(SImage)
						.Image(&MyCustomWidgetStyle->MyBrush)
				]
				+ SGridPanel::Slot(1, 0)
				[
					SNew(SImage)
						.Image(&MyCustomWidgetStyle->MyBrush)
				]
				+ SGridPanel::Slot(1, 1)
				[
					SNew(SImage)
						.Image(&MyCustomWidgetStyle->MyBrush)
				]
		];
	//SScrollBox
	AddSlot()
		.Position(FVector2D(700, 50))
		.Size(FVector2D(100, 200))
		[
			SNew(SScrollBox)
				+SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom1"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom2"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom3"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom4"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom5"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom6"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom7"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom8"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom9"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Custom10"))
						.Font(MyCustomWidgetStyle->MyFont)
				]
		];
	//SMultiLineEditableText
	static FSlateColorBrush MySlateColorBrush = FSlateColorBrush(FLinearColor(1, 1, 1, 0.5));
	AddSlot()
		.Position(FVector2D(900, 50))
		.Size(FVector2D(200, 200))
		[
			SNew(SBorder)
				.BorderImage(&MySlateColorBrush)
				[
					SNew(SMultiLineEditableText)
						.Font(MyCustomWidgetStyle->MyFont)
						.HintText(LOCTEXT("text", "请输入内容"))
				]
		];
	//SWrapBox
	AddSlot()
		.Position(FVector2D(900, 300))
		.Size(FVector2D(200, 100))
		[
			SNew(SWrapBox)
				.InnerSlotPadding(FVector2D(5, 5))
				+SWrapBox::Slot()
				[
					SNew(SImage)
						.Image(&MyCustomWidgetStyle->MyBrush)
				]
				+ SWrapBox::Slot()
				[
					SNew(SImage)
						.Image(&MyCustomWidgetStyle->MyBrush)
				]
				+ SWrapBox::Slot()
				[
					SNew(SImage)
						.Image(&MyCustomWidgetStyle->MyBrush)
				]
		];
	//STreeView
	TreeItems.Add(MakeShared<FString>("ParentA"));
	TreeItems.Add(MakeShared<FString>("ParentB"));
	TreeItems.Add(MakeShared<FString>("ParentC"));

	ChildrenMap.Add("ParentA", TArray<TSharedPtr<FString>>{MakeShared<FString>("ChildrenA")});
	ChildrenMap.Add("ParentB", TArray<TSharedPtr<FString>>{MakeShared<FString>("ChildrenB1"), MakeShared<FString>("ChildrenB2")});
	ChildrenMap.Add("ParentC", TArray<TSharedPtr<FString>>{MakeShared<FString>("ChildrenC1"), MakeShared<FString>("ChildrenC2"), MakeShared<FString>("ChildrenC3")});

	AddSlot()
		.Position(FVector2D(900, 400))
		.Size(FVector2D(200, 100))
		[
			SNew(STreeView<TSharedPtr<FString>>)
				.TreeItemsSource(&TreeItems)
				.OnGenerateRow(this, &SMyCanvas::OnGenerateRowForTree)
				.OnGetChildren(this, &SMyCanvas::OnGenerateChildrenForTree)
		];
	ListItems.Add(MakeShared<FString>("111"));
	ListItems.Add(MakeShared<FString>("222"));
	ListItems.Add(MakeShared<FString>("333"));
	//SListView
	AddSlot()
		.Position(FVector2D(500, 800))
		.Size(FVector2D(100, 100))
		[
			SNew(SListView<TSharedPtr<FString>>)
				.ListItemsSource(&ListItems)
				.OnGenerateRow(this, &SMyCanvas::OnGenerateRowForList)
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
TSharedRef<ITableRow> SMyCanvas::OnGenerateRowForTree(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTab)
{

	return SNew(STableRow<TSharedPtr<FString>>, OwnerTab)
		[
			SNew(STextBlock)
				.Text(FText::FromString(*Item))
		];
}
void SMyCanvas::OnGenerateChildrenForTree(TSharedPtr<FString> Item, TArray<TSharedPtr<FString>>& OutChildren)
{
	const TArray<TSharedPtr<FString>>* FindChildren = ChildrenMap.Find(*Item);
	if (FindChildren)
	{
		OutChildren = *FindChildren;
	}
}
TSharedRef<ITableRow> SMyCanvas::OnGenerateRowForList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTab)
{
	return SNew(STableRow<TSharedPtr<FString>>, OwnerTab)
		[
			SNew(STextBlock)
				.Text(FText::FromString(*Item))
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
