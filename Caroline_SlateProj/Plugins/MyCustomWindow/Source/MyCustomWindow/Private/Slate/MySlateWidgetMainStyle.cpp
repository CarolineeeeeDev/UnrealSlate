// Lehan Li's Slate Learning Project


#include "Slate/MySlateWidgetMainStyle.h"

const FName FMainWidgetStyle::TypeName(TEXT("MainWidgetStyle"));

const FName FMainWidgetStyle::GetTypeName() const
{
	return TypeName;
}

const FMainWidgetStyle& FMainWidgetStyle::GetDefault()
{
	static FMainWidgetStyle MyWidgetStyle;
	return MyWidgetStyle;
}

const FSlateWidgetStyle* const UMySlateWidgetMainStyle::GetStyle() const
{
	return static_cast<const struct FSlateWidgetStyle*>(&MyWidgetStyle);
}