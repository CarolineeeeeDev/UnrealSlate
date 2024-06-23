// Lehan Li's Slate Learning Project

#include "Slate/MyHUD.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	MyClass = LoadClass<UUserWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Slate/UMG_Test.UMG_Test'"));
	MyUserWidget = CreateWidget<UUserWidget>(GetWorld(), MyClass);
	ShowMySlate();
}

void AMyHUD::ShowMySlate()
{
	if (GEngine && GEngine->GameViewport)
	{
		MyCompoundWidget = SNew(SMyCompoundWidget).OwnerHUDArg(this).OwnerWidgetArg(MyUserWidget);
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
