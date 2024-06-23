// Lehan Li's Slate Learning Project

#pragma once

#include "CoreMinimal.h"
#include "MyHUD.h"
#include "Widgets/SCompoundWidget.h"

class AMyHUD;

class CAROLINE_SLATEPROJ_API SMyCompoundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyCompoundWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<AMyHUD>, OwnerHUDArg)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply OnPlayClick() const;
	FReply OnQuitClick() const;

private:
	TWeakObjectPtr<AMyHUD> MyOwnerHUD;
};
