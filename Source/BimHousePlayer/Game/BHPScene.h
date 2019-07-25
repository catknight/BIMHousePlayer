// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include "Paths.h"
#include "ProceduralMeshComponent.h"
#include "NoExportTypes.h"
#include "BHPScene.generated.h"


/************************************************************************/
/*以下是mesh解析相关数据格式                                                                   */
/************************************************************************/
 // 纹理类型
UENUM(BlueprintType)
enum ETextureType
{
	ETextureTypeDiffuse = 1,  // 漫反射
	ETextureTypeSpecular = 2, // 镜面反射
};

USTRUCT(BlueprintType)
struct FBHPMesh
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHMesh")
		TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHMesh")
		TArray<int32> Indices;//顶点索引
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHMesh")
		TArray<FVector> Normals;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHMesh")
		TArray<FVector2D> UV0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHMesh")
		TArray<FLinearColor> VertexColors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHMesh")
		TArray<FProcMeshTangent> Tangents;//切线

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHMesh")
		FTransform RelativeTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHMesh")
		FString Name;//Mesh名称

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHMesh")
		int32 Index;//顶点索引
	
	int64 GUID;//唯一编号
	int64 MatGUID;//引用的材质

	TArray<FBHPMesh*>Child;

};



USTRUCT(BlueprintType)
struct FBHPTexture
{
	GENERATED_BODY()

	int64 id;
	aiTextureType type;
	FString path;


};



USTRUCT(BlueprintType)
struct FBHPCam
{
	GENERATED_BODY()


};


/************************************************************************/
/* 以下是.bhp文件数据格式                                                                     */
/************************************************************************/
USTRUCT()
struct FSystemInfo
{
	GENERATED_BODY()

	
	double version;

	
	bool  leftHand;

	
	FString up;

	
	FString unit;

};

USTRUCT()
struct FMesh
{
	GENERATED_BODY()
	FString guid;//模型guid
	FString name;//模型名称
	FString suffix;//模型文件后缀
	FString currentMaterial;//当前材质
	TArray<FString>materialList;//可替换材质列表
	TArray<FString>meshList;//可替换模型列表
	FString roomID;//所属的空间ID
	double saleType;//销售信息，1标配项，2增配项，3升级项
	FString meshType;//模型类型，有door，window，floor，wall，roof，设置碰撞属性用的，
	FVector position;
	FVector rotation;
	FVector scaler;
	TArray<FBHPMesh>Mesh;


};
USTRUCT()
struct FBHPLight
{
	GENERATED_BODY()
	FString guid;//
	FString name;//
	FString type;//灯光类型：point，area，spot，direct	
	FVector position;
	FVector rotation;
	FVector scale;
	FVector target;
	double angle;
	double length;
	double width;
	FVector4 color;
	double strength;

};
USTRUCT()
struct FBHPMaterial
{
	GENERATED_BODY()

	FString name;//
	FString type;//材质类型，预设金属，玻璃，木材，大理石，布料，塑料等材质（待定）	
	FVector4 baseColor;
	FString diffuseMap;
	double UVOffsetX;//UV偏移
	double UVOffsetY;
	double UVScaleX;//UV缩放
	double UVScaleY;
	double UVAngle;//UV旋转角度
	double metallic;//金属性,UE4 PBR材质属性，范围0-1.0
	double roughness;//粗糙度，UE4 PBR材质属性，范围0-1.0
	double specular;//高光度， UE4 PBR材质属性，范围0-1.0
	bool emissive; //是否自发光
	double opacity; //不透明度


};
USTRUCT()
struct FRoom
{
	GENERATED_BODY()

	FString roomID;
	TArray<FString>additions;

};

USTRUCT()
struct FHome
{
	GENERATED_BODY()

	FString style;
	TArray<FRoom> room;
	TArray<FMesh> mesh;
	TArray<FString>Material;
	TArray<FBHPLight> light;

};

UCLASS()
class BIMHOUSEPLAYER_API UBHPScene : public UObject
{
	GENERATED_BODY()
		UBHPScene();
public:
	UPROPERTY()
	TArray<FBHPMesh> Meshes;

	FSystemInfo sceneSystemInfo;

	TArray<FHome> sceneHomes;

	

	//UPROPERTY(EditAnywhere, Category = "BPHScene")
	//TArray<FBHPMaterial> Materials;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHScene")
	//TArray<FBHPLight> Lights;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHScene")
	//TArray<FBHPCam> Cameras;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BPHScene")
	//TArray<FBHPTexture> Textures;

	UFUNCTION()
		bool ImportSceneFromFile(FString file);

	UFUNCTION()
		bool ImportSceneFromNet(FString file);


	

	UFUNCTION()
		bool GetAllModelFromLocal();//获取本地model

	UFUNCTION()
		bool GetModelFromLocal(FString guid,FString suffix);//获取本地model

	UFUNCTION()
		bool DownloadAllModel();//本地没有模型，获取远程model

	UFUNCTION()
		bool DownloadModel(FString guid);//本地没有模型，获取远程model

	UFUNCTION()
		bool GetLocalMat(FString guid);//本地没有模型，获取远程model

	UFUNCTION()
		bool DownloadRemoteMat(FString guid);//本地没有模型，获取远程model




	UFUNCTION()
		bool ParseModelFromFile(FString file);//解析mesh
	UFUNCTION()
		bool ImportModelFromNet(FString file);//解析远程mesh
	
		void FindMesh(const aiScene* scene, aiNode* node);
		void FindMeshInfo(const aiScene* scene, aiNode* node);

		
		
		
private:
	int NumMeshes;
	int NumMaterials;
	int NumLights;
	int NumCameras;

	bool processNode2(const aiScene* scenePtr);
	bool processNode(const aiNode* node, const aiScene* sceneObjPtr);
	bool processMesh(const aiMesh* meshPtr, const aiScene* sceneObjPtr, FBHPMesh& meshObj);
	bool processMaterial(const aiMaterial* matPtr, const aiScene* sceneObjPtr, const aiTextureType textureType, TArray<FBHPTexture>& textures);
	
	

};
