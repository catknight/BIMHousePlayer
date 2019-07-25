// Fill out your copyright notice in the Description page of Project Settings.

#include "BHPModeBase.h"
#include "BHPController.h"
#include "UI/HUD/BHPHUD.h"
#include "BHPInstance.h"


ABHPModeBase::ABHPModeBase()
{
	
		HUDClass = ABHPHUD::StaticClass();
		PlayerControllerClass = ABHPController::StaticClass();
		
		
}



void ABHPModeBase::BeginPlay()
{
	MainScene = NewObject<UBHPScene>();
	//MainScene->AddToRoot();
	WorldGen = NewObject<UBHPObjGen>();
	WorldGen->CurrentWorld = GetWorld();
	//WorldGen->AddToRoot();

	
	//GetGameInstance<UBHPInstance>()->CurrentWorld =GetWorld();
}
