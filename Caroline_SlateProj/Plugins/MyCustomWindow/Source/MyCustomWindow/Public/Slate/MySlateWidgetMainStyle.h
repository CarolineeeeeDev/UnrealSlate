// Lehan Li's Slate Learning Project

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateBrush.h"
#include "Fonts/SlateFontInfo.h"
#include "Sound/SlateSound.h"
#include "Math/Color.h"
#include "MySlateWidgetMainStyle.generated.h"

USTRUCT()
struct FMainWidgetStyle :public FSlateWidgetStyle
{
	GENERATED_BODY()
public:
	virtual void GetResource(TArray<const FSlateBrush*>& OutBrushes) const {};
	virtual const FName GetTypeName() const;
	static const FMainWidgetStyle& GetDefault();
	static const FName TypeName;

	UPROPERTY(EditAnywhere, Category = "MySlate")
	FSlateBrush MyBrush;
	UPROPERTY(EditAnywhere, Category = "MySlate")
	FSlateFontInfo MyFont;
	UPROPERTY(EditAnywhere, Category = "MySlate")
	FSlateSound MySound;
	UPROPERTY(EditAnywhere, Category = "MySlate")
	FLinearColor MyColor;
};

UCLASS()
class MYCUSTOMWINDOW_API UMySlateWidgetMainStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "MyWidgetStyle", meta = (ShowOnlyInnerProperties))
	FMainWidgetStyle MyWidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override;
	
};
