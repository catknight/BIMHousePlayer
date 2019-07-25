// Fill out your copyright notice in the Description page of Project Settings.

#include "BHPMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Frame/BHPUtil.h"
#include "ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"

// Sets default values
ABHPMeshActor::ABHPMeshActor()
{
 	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	//RootComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.bStartWithTickEnabled = true;

	MeshComponet = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	MeshComponet->SetMobility(EComponentMobility::Movable);
	//MeshComponet->RegisterComponent();
	MeshComponet->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FString path = "Material'/Game/Material/base.base'";
	CurrentMateril= Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,*path));
	
	
	//FScriptDelegate DelegateHit;
	//DelegateHit.BindUFunction(this, "OnHit");
	//MeshComponet->OnComponentHit.Add(DelegateHit);

	MeshComponet->bUseAsyncCooking = true;
	MeshComponet->bUseComplexAsSimpleCollision = true;
	//MeshComponet->SetSimulatePhysics(true);
	MeshComponet->SetVisibility(true);
	MeshComponet->OnComponentHit.AddDynamic(this, &ABHPMeshActor::OnHit);

	FScriptDelegate DelegateClick;
	DelegateClick.BindUFunction(this, "OnClicked");
	MeshComponet->OnClicked.Add(DelegateClick);
	//OnClicked.AddDynamic(this, &ABHPMeshActor::OnClicked);

	FScriptDelegate DelegateIn;
	DelegateIn.BindUFunction(this, "OnBeginMouseIn");
	this->OnBeginCursorOver.Add(DelegateIn);
	//this->OnBeginCursorOver.AddDynamic(this, &ABHPMeshActor::OnBeginMouseIn);

	FScriptDelegate DelegateOut;
	DelegateOut.BindUFunction(this, "OnEndMouseIn");
	this->OnEndCursorOver.Add(DelegateOut);
	//this->OnBeginCursorOver.AddDynamic(this, &ABHPMeshActor::OnEndMouseIn);


	
	
	

	/*if (PlayerInputComponent) {

		PlayerInputComponent->BindAction("PopMenu", IE_Pressed, this, &ABHPMeshActor::popMenu);

		PlayerInputComponent->BindAction("PopMenu", IE_Released, this, &ABHPMeshActor::popMenu);
	}*/
	//MeshComponet->bRenderCustomDepth=true;

	//this->OnEndCursorOver.AddDynamic(this, &ABHPMeshActor::OnEndMouseIn);
	//OnBeginCursorOver.AddDynamic(this, &ABHPMeshActor::OnBeginMouseIn);

	
	
	
}
void ABHPMeshActor::Tick(float time)
{
	Super::Tick(time);
	


}

/*void ABHPMeshActor::SetupPlayerInputComponent(class UInputComponent * InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	

	//InputComponent
	InputComponent->BindAction("PopMenu", IE_Pressed, this, &ABHPMeshActor::popMenu);

	InputComponent->BindAction("PopMenu", IE_Released, this, &ABHPMeshActor::popMenu);
}*/

void ABHPMeshActor::popMenu()
{
	BHPLogger::Error(TEXT("右键弹出菜单") + this->GetName(), 6);

}

void ABHPMeshActor::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld() != nullptr)
	{
		APlayerController*play = GetWorld()->GetFirstPlayerController();
		if (play != nullptr)
		{
			EnableInput(play);
		}

	}
/*
	if (PlayerInputComponent) {

		PlayerInputComponent->BindAction("PopMenu", IE_Pressed, this, &ABHPMeshActor::popMenu);

		PlayerInputComponent->BindAction("PopMenu", IE_Released, this, &ABHPMeshActor::popMenu);
	}*/
}

void ABHPMeshActor::OnClicked()
{
  BHPLogger::Error(TEXT("点击了")+this->GetName(), 6);

 


}

void ABHPMeshActor::OnBeginMouseIn(UPrimitiveComponent* OtherComp)
{
	BHPLogger::Error(TEXT("鼠标HoverIn") + this->GetName(), 2);

	Cast<UPrimitiveComponent>(this->MeshComponet)->SetRenderCustomDepth(true);
	

}

void ABHPMeshActor::OnEndMouseIn(UPrimitiveComponent* OtherComp)
{
	BHPLogger::Error(TEXT("鼠标HoverOut") + this->GetName(), 2);
	Cast<UPrimitiveComponent>(this->MeshComponet)->SetRenderCustomDepth(false);

	


}

void ABHPMeshActor::GenMeshSelf(FBHPMesh &mesh)
{

	MeshComponet->CreateMeshSection_LinearColor(mesh.Index,mesh.Vertices, mesh.Indices, mesh.Normals, mesh.UV0, mesh.VertexColors, mesh.Tangents, true);
	MeshComponet->SetWorldTransform(FTransform(FRotator(0, 90, -90),FVector(0,0,0),FVector(1,1,1)));
	if (CurrentMateril!=nullptr)
	{
		MeshComponet->SetMaterial(0, CurrentMateril);

	}
	else
	{
		BHPLogger::Error(TEXT("材质未找到"), 2);
	}
	//MeshComponet->AddToRoot();
	//MeshComponet->SetMaterial();
	//MeshComponet->RegisterComponent();
	//MeshComponet->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	

	/*FString boxname = "Box_" +FString::FromInt(mesh.Index);
	 box = CreateDefaultSubobject<UStaticMeshComponent>(FName(*boxname));

	auto BoxMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (BoxMesh.Object!=nullptr)
	{
		box->SetStaticMesh(BoxMesh.Object);
	}
	box->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	*/
	//MeshComponet->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//MeshComponet->SetCollisionResponseToAllChannels(ECR_Block);
	//MeshComponet->SetCollisionProfileName(TEXT("BlackAll"));
	//MeshComponet->OnClicked.AddDynamic(this, &ABHPMeshActor::OnHit);

	//MeshComponet->SetWorldRotation(FRotator(180, 0, 0));
	//MeshComponet->SetRelativeScale3D(FVector(100,100,100));

}

void ABHPMeshActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	BHPLogger::Error(TEXT("碰到了")+ Hit.Actor->GetName(), 6);
	
	//MeshComponet->bRenderCustomDepth(true);
	//HitComponent->SetRenderCustomDepth(true);
	//HitComponent->CustomDepthStencilValue = STENCIL_NEUTRAL_OUTLINE;

	//OtherComponent->SetRenderCustomDepth(true);
	//HitComponent->CustomDepthStencilValue = STENCIL_NEUTRAL_OUTLINE;

}

