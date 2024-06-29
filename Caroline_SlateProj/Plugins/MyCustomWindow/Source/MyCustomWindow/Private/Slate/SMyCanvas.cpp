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
}
FReply SMyCanvas::OnClickButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Button Clicked"));
	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
