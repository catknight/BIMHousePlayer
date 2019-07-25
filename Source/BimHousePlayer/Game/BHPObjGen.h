// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "BHPScene.h"
#include "BHPMeshActor.h"

#include "BHPObjGen.generated.h"


UCLASS()
class BIMHOUSEPLAYER_API UBHPObjGen : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UBHPObjGen();
	//UStaticMeshComponent *root;
	//UActorComponent* RootComponent;
	UPROPERTY(EditAnywhere)
	USceneComponent* RootScene;
	TArray<ABHPMeshActor*> SceneActors;
	UWorld* CurrentWorld;

public:	
	// Called every frame
	
	 void GenMesh(FHome scene);


};
