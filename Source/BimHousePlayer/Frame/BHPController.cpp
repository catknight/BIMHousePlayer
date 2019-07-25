// Fill out your copyright notice in the Description page of Project Settings.

#include "BHPController.h"

ABHPController::ABHPController()
{
	static ConstructorHelpers::FClassFinder<UBHPPopMenu> PopMenu(TEXT("/Game/UI/PopMenu")); // 找到蓝图类WidgetBlueprint'/Game/UI/PopMenu.PopMenu'
	if (PopMenu.Succeeded())
	{
		PopMenuClass = PopMenu.Class; // 得到class
	}

	

}
void ABHPController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI inputMode;
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputMode.SetHideCursorDuringCapture(false);
	SetInputMode(inputMode);
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	//EnableInput(this);

	InputComponent->BindAction("PopMenu", IE_Pressed, this, &ABHPController::PopMenu);


	if (PopMenuClass)
	{
		PopMenuInstance = CreateWidget<UBHPPopMenu>(GetWorld(), PopMenuClass);
		
	}

	//lastActor = Cast<ABHPMeshActor>();


}

void ABHPController::Tick(float time)
{
	Super::Tick(time);
	RunRayCast();
	//RunCheckMouseEvent();



}

FHitResult ABHPController::GetRayHit(FVector start, FVector end)
{
	//FCollisionQueryParams CollParam(FName(TEXT("Select")),true,this);
	//CollParam.bReturnPhysicalMaterial = true;
	FHitResult Hit(ForceInit);
	UWorld* world = GetWorld();
	if (world != nullptr)
	{
		FCollisionQueryParams  TraceParams(FName(TEXT("Actor")), true, this);//给射线定义碰撞，并取一个名字

		TraceParams.bTraceAsyncScene = true;//场景中所有碰撞
		TraceParams.bReturnPhysicalMaterial = false;//物理材质碰撞
		TraceParams.bTraceComplex = true;


		FHitResult hit(ForceInit);//初始化射线类并且发射一个射线
		GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, TraceParams);
		if (Cast<AActor>(hit.GetActor()))//打印被射线碰撞的物体
		{
			//GEngine->AddOnScreenDebugMessage(-1, 0.8f, FColor::Blue, hit.GetActor()->GetName());
			//BHPLogger::Debug(hit.GetActor()->GetName(), 1);



		}

		if (Cast<ABHPMeshActor>(hit.GetActor()))//打印被射线碰撞的物体
		{
			ABHPMeshActor* actor = Cast<ABHPMeshActor>(hit.GetActor());
			UPrimitiveComponent* cmp;
			if (lastActor != nullptr)
			{
				cmp = Cast<UPrimitiveComponent>(lastActor->MeshComponet);
				cmp->SetRenderCustomDepth (false);

			}
			//actor->MeshComponet->com//bRenderCustomDepth=true;

			cmp = Cast<UPrimitiveComponent>(actor->MeshComponet);
			cmp->SetRenderCustomDepth(true);

			lastActor = actor;
			//GEngine->AddOnScreenDebugMessage(-1, 0.8f, FColor::Blue, hit.GetActor()->GetName());
			//BHPLogger::Debug(hit.GetActor()->GetName(), 1);
		}
		else
		{
			if (lastActor != nullptr)
			{
				UPrimitiveComponent* c = Cast<UPrimitiveComponent>(lastActor->MeshComponet);
				c->SetRenderCustomDepth(false);

			}
		}






		/*GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			Hit.Actor;
		}
		else
		{
			BHPLogger::Debug(TEXT("No Selected"), 5);

		}*/


	}

	return Hit;


}

void ABHPController::RunRayCast()
{
	FVector Start(0);
	FVector End(0);
	FVector CamLoc;
	FRotator CamRot;


	//得到摄像机位置和方向
	this->GetPlayerViewPoint(CamLoc, CamRot);
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc)
	{
		ULocalPlayer* localplayer = pc->GetLocalPlayer();

		FVector Dir, pint;
		if (pc->DeprojectMousePositionToWorld(pint, Dir))//得到鼠标点击的位置和方向
		{
			FVector TraceStar = CamLoc;//摄像机所在位置
			FVector Direction = CamRot.Vector();//摄像机所看方向//实际上这个方向也可以发射一个射线出去，判断是否在前方
			//射线的终点
			FVector TranceEnd = TraceStar + (Dir * 10000);//射线的终点
			GetRayHit(TraceStar, TranceEnd);

		}

	}


}

void ABHPController::PopMenu()
{
	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		if (Cast<ABHPMeshActor>(Hit.GetActor()))
		{
			BHPLogger::Debug(TEXT("鼠标右键：") + Hit.GetActor()->GetName(), 9);
			if (PopMenuInstance!=nullptr)
			{
				PopMenuInstance->AddToViewport();
			}
			


		}
	}else 
	{
		if (PopMenuInstance != nullptr)
		{
			PopMenuInstance->RemoveFromViewport();
		}

	}
}
