// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCustomWindowStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FMyCustomWindowStyle::StyleInstance = nullptr;

void FMyCustomWindowStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FMyCustomWindowStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FMyCustomWindowStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("MyCustomWindowStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon32x32(32.0f, 32.0f);

TSharedRef< FSlateStyleSet > FMyCustomWindowStyle::Create()
{
	/*TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("MyCustomWindowStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("MyCustomWindow")->GetBaseDir() / TEXT("Resources"));*/
	//Style->Set("MyCustomWindow.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	//Style->Set("MyCustomWindow.OpenPluginWindow", new IMAGE_BRUSH(TEXT("MyCustomButtonIcon"), Icon32x32));
	TSharedRef< FSlateStyleSet > Style = FSlateGameResources::New(FMyCustomWindowStyle::GetStyleSetName(), "/Game/Slate/MySlateWidgetStyle", "/Game/Slate/MySlateWidgetStyle");
	FString IconString = IPluginManager::Get().FindPlugin("MyCustomWindow")->GetBaseDir() / TEXT("Resources/MyCustomButtonIcon.png");
	Style->Set("MyCustomWindow.OpenPluginWindow", new FSlateImageBrush(IconString, Icon32x32));
	return Style;
}

void FMyCustomWindowStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FMyCustomWindowStyle::Get()
{
	return *StyleInstance;
}
