// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Game/BHPScene.h"
#include "Game/BHPObjGen.h"
#include "BHPModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BIMHOUSEPLAYER_API ABHPModeBase : public AGameModeBase
{
	GENERATED_BODY()

		ABHPModeBase();
public:
	UPROPERTY()
	UBHPScene* MainScene;
	UBHPObjGen* WorldGen;
	void BeginPlay();
	
};
