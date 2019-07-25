// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "BHPMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BIMHOUSEPLAYER_API UBHPMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
		UButton*Button_Open;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton*Button_Net;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton*Button_Setting;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton*Button_VR;

	virtual bool Initialize() override;

	UFUNCTION()
		void OpenLoaclScene();
	UFUNCTION()
		void GetNetScene();
	UFUNCTION()
		void WorldSetting();
	UFUNCTION()
		void InterVR();

	
};
