// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BHPHUD.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class BIMHOUSEPLAYER_API ABHPHUD : public AHUD
{
	GENERATED_BODY()


		ABHPHUD();
public:
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UBHPHUDWidget>BHPHUDClass;
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UBHPMenuWidget>BHPMenuClass;

private:
   void	BeginPlay();

  
	
};
