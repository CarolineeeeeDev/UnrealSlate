// Lehan Li's Slate Learning Project

#include "Slate/MyHUD.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMySlate();
}

void AMyHUD::ShowMySlate()
{
	if (GEngine && GEngine->GameViewport)
	{
		MyCompoundWidget = SNew(SMyCompoundWidget);
		//第一种添加Slate到视口
		GEngine->GameViewport->AddViewportWidgetContent(MyCompoundWidget.ToSharedRef());//智能指针转化为智能引用
		//第二种添加Slate到视口
		//GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(MyCompoundWidget.ToSharedRef()));//智能指针转化为智能引用
	}
}

void AMyHUD::RemoveMySlate()
{
	if (GEngine && GEngine->GameViewport && MyCompoundWidget)
	{
		//第一种移除视口上的Slate
		GEngine->GameViewport->RemoveViewportWidgetContent(MyCompoundWidget.ToSharedRef());
		//第二种移除视口上的Slate
		//GEngine->GameViewport->RemoveViewportWidgetContent(WidgetContainer.ToSharedRef());
	}
}
