// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BHPScene.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "BHPMeshActor.generated.h"


/* Stencil index mapping to PP_OutlineColored */
#define STENCIL_FRIENDLY_OUTLINE 252;
#define STENCIL_NEUTRAL_OUTLINE 253;
#define STENCIL_ENEMY_OUTLINE 254;
#define STENCIL_ITEMHIGHLIGHT 255;

UCLASS()
class BIMHOUSEPLAYER_API ABHPMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent* MeshComponet;
	UStaticMeshComponent* box;
	
	UPROPERTY(EditAnywhere)
	UMaterial* MaterialComponet;
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> Materials;//含有替换材质

	UPROPERTY(EditAnywhere)
	UMaterialInterface* CurrentMateril;//当前材质

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* MatDynamic;
	// Sets default values for this actor's properties

	 

	ABHPMeshActor();
protected:
	FBHPMesh mesh;

public:	
	
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
		void popMenu();
	virtual void BeginPlay() override ;
	virtual void Tick(float DeltaSeconds)override;
	UPROPERTY()
	UInputComponent *PlayerInputComponent;
	UFUNCTION()
	void OnClicked();
	UFUNCTION()
	void OnBeginMouseIn(UPrimitiveComponent* OtherComp);
	UFUNCTION()
	void OnEndMouseIn(UPrimitiveComponent* OtherComp);

	void GenMeshSelf(FBHPMesh &mesh);

	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
