// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BHPUtil.h"
#include "../UI/Widget/BHPPopMenu.h"
#include "BHPController.generated.h"

/**
 * 
 */
UCLASS()
class BIMHOUSEPLAYER_API ABHPController : public APlayerController
{
	GENERATED_BODY()

public:
	 ABHPController();
	UPROPERTY()
		TSubclassOf<UBHPPopMenu>PopMenuClass;
	UPROPERTY()
		UBHPPopMenu* PopMenuInstance;

	ABHPMeshActor* lastActor;
	virtual void BeginPlay() override;
	void Tick(float time)override;
	FHitResult GetRayHit(FVector start,FVector end);
	void RunRayCast();
	void PopMenu();
};
