// Lehan Li's Slate Learning Project

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class CAROLINE_SLATEPROJ_API SMyCompoundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyCompoundWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
