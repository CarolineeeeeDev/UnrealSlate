// Lehan Li's Slate Learning Project

#pragma once

#include "CoreMinimal.h"
#include "SMyCompoundWidget.h"
#include "Widgets/SWeakWidget.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class CAROLINE_SLATEPROJ_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void ShowMySlate();
	void RemoveMySlate();

private:
	TSharedPtr<SMyCompoundWidget> MyCompoundWidget;
	TSharedPtr<SWeakWidget> WidgetContainer;
};
