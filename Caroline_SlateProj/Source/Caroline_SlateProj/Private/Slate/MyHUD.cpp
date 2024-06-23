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
		MyCompoundWidget = SNew(SMyCompoundWidget).OwnerHUDArg(this);
		//��һ�����Slate���ӿ�
		GEngine->GameViewport->AddViewportWidgetContent(MyCompoundWidget.ToSharedRef());//����ָ��ת��Ϊ��������
		//�ڶ������Slate���ӿ�
		//GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(MyCompoundWidget.ToSharedRef()));//����ָ��ת��Ϊ��������
	}
}

void AMyHUD::RemoveMySlate()
{
	if (GEngine && GEngine->GameViewport && MyCompoundWidget)
	{
		//��һ���Ƴ��ӿ��ϵ�Slate
		GEngine->GameViewport->RemoveViewportWidgetContent(MyCompoundWidget.ToSharedRef());
		//�ڶ����Ƴ��ӿ��ϵ�Slate
		//GEngine->GameViewport->RemoveViewportWidgetContent(WidgetContainer.ToSharedRef());
	}
}
