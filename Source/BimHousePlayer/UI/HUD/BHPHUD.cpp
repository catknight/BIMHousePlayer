// Fill out your copyright notice in the Description page of Project Settings.

#include "BHPHUD.h"
#include "UI/Widget/BHPHUDWidget.h"
#include "UI/Widget/BHPMenuWidget.h"
#include "UObject/ConstructorHelpers.h"



ABHPHUD::ABHPHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UBHPHUDWidget(TEXT("/Game/UI/BHPHUDWidget_BP")); // �ҵ���ͼ��
	if (UBHPHUDWidget.Succeeded())
	{
		BHPHUDClass = UBHPHUDWidget.Class; // �õ�class
	}


}

void ABHPHUD::BeginPlay()
{
		Super::BeginPlay();
		

		if (BHPHUDClass) 
		{
			UBHPHUDWidget* HudWidget = CreateWidget<UBHPHUDWidget>(GetWorld(), BHPHUDClass);
			if (HudWidget != nullptr)
			{
				HudWidget->AddToViewport();

			}

		}
		

		

}
