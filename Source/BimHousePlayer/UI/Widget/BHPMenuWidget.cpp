// Fill out your copyright notice in the Description page of Project Settings.

#include "BHPMenuWidget.h"
#include "Engine/GameEngine.h"
#include "SlateApplication.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Frame/BHPUtil.h"
#include "Frame/BHPInstance.h"
#include "Frame/BHPModeBase.h"



bool UBHPMenuWidget::Initialize()
{


	Super::Initialize();

	if (Button_Open!=nullptr)
	{
		Button_Open->OnClicked.AddDynamic(this,&UBHPMenuWidget::OpenLoaclScene);
	}

	if (Button_Net != nullptr)
	{
		Button_Net->OnClicked.AddDynamic(this, &UBHPMenuWidget::GetNetScene);
	}

	if (Button_Setting != nullptr)
	{
		Button_Setting->OnClicked.AddDynamic(this, &UBHPMenuWidget::WorldSetting);
	}

	if (Button_VR != nullptr)
	{
		Button_VR->OnClicked.AddDynamic(this, &UBHPMenuWidget::InterVR);
	}

	

	return false;
}

void UBHPMenuWidget::OpenLoaclScene()
{
	//GEngine->AddOnScreenDebugMessage(1, 6, FColor(255, 0, 0), FString("Opened"));

	void* ParentWindowPtr = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();

	// 保存打在开对话框中选择的文件
	TArray<FString> OutFiles;
	//FString FileTypes = TEXT("*.udatasmith *.fbx *.def|*.udatasmith;*.fbx;*.def|All Files|*.*");//iOS packaged applications (*.ipa)|*.ipa|All Files (*.*)|*.*
	FString FileTypes = TEXT("*.bhp|*.bhp|All Files|*.*");//iOS packaged applications (*.ipa)|*.ipa|All Files (*.*)|*.*

	bool openOK=DesktopPlatform->OpenFileDialog(ParentWindowPtr,TEXT("Open BimHousePlayer Scene"),TEXT("C://"),TEXT("Setup.sh"),
		FileTypes,
		EFileDialogFlags::None,
		OutFiles
	);

	if (openOK)
	{			
		BHPLogger::Debug(OutFiles[0], 6);
		AGameModeBase* game = GetWorld()->GetAuthGameMode();
		if (Cast<ABHPModeBase>(game)->MainScene->ImportSceneFromFile(OutFiles[0]))
		{

			//BHPLogger::Error(Cast<ABHPModeBase>(game)->MainScene->sceneSystemInfo.unit,6);
			Cast<ABHPModeBase>(game)->WorldGen->GenMesh(Cast<ABHPModeBase>(game)->MainScene->sceneHomes[0]);
		}
		else
		{

		}
		
		//if (GetGameInstance())
		//{
			//UGameInstance* instance = GetGameInstance();

			
			//Cast<UBHPInstance>(instance)->MainScene->ImportSceneFromFile(OutFiles[0]);
		//}
		//UBHPUtil::ImportMeshFromFile(OutFiles[0]);
	
		
	}
	else
	{
		OutFiles;
		BHPLogger::Error(TEXT("没有选择任何文件"), 6);	
	}

	
	//return openOK;


}

void UBHPMenuWidget::GetNetScene()
{
	BHPLogger::Debug(TEXT("网络连接"), 6);

}

void UBHPMenuWidget::WorldSetting()
{
	BHPLogger::Debug(TEXT("系统设置"), 6);

}

void UBHPMenuWidget::InterVR()
{
	BHPLogger::Debug(TEXT("漫游模式"), 6);

}
