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

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnClickButton();
};
