// Fill out your copyright notice in the Description page of Project Settings.

#include "BHPObjGen.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
UBHPObjGen::UBHPObjGen()
{
 
	

}

// Called when the game starts or when spawned




void UBHPObjGen::GenMesh(FHome home)
{
	if (CurrentWorld!=nullptr)
	{
		for (FMesh meshit:home.mesh) 
		{
			for (int32 i = 0; i < meshit.Mesh.Num(); i++)
			{
				FActorSpawnParameters ActorSpawnParameters;

				ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				ActorSpawnParameters.ObjectFlags = EObjectFlags::RF_Transient;
				ABHPMeshActor* mesh = CurrentWorld->SpawnActor<ABHPMeshActor>(ABHPMeshActor::StaticClass(), ActorSpawnParameters);
				mesh->GenMeshSelf(meshit.Mesh[i]);
				//mesh->AddToRoot();
				//mesh->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
				//mesh->AttachToComponent(RootScene, FAttachmentTransformRules::KeepRelativeTransform);

				//FString boxname = "Box" + FString::FromInt(i);
				//UStaticMeshComponent* box = CreateDefaultSubobject<UStaticMeshComponent>(FName(*boxname));

				/*auto BoxMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
				if (BoxMesh.Object!=nullptr)
				{
					//box->SetStaticMesh(BoxMesh.Object);
				}*/
				//box->AttachToComponent(RootScene, FAttachmentTransformRules::KeepRelativeTransform);


				//mesh->AddToRoot();
				//SceneActors.Push(mesh);

			}


		}
		
		
		//Root->RegisterComponent();
	}
	

}

