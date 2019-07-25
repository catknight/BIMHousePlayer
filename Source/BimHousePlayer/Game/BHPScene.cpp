// Fill out your copyright notice in the Description page of Project Settings.

#include "BHPScene.h"
#include "Frame/BHPUtil.h"
#include "Object.h"
#include "Frame/BHPInstance.h"
#include "ProceduralMeshComponent.h"
#include "Json.h"

UBHPScene::UBHPScene()
{
	

}

bool UBHPScene::ImportSceneFromFile(FString filePath)
{
	if (!(FPaths::FileExists(filePath)))
	{
		FString str = TEXT("模型文件不存在，导入失败:") + filePath;
		BHPLogger::Error(str, 1);
		return false;
	}
	else
	{
		FString content;
		//FArchive* const File = IFileManager::Get().CreateFileReader(*filePath);
		if (FFileHelper::LoadFileToString(content,*filePath))
		{
			TSharedPtr<FJsonObject>root = MakeShareable(new FJsonObject);
			try
			{
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(content);
				if (FJsonSerializer::Deserialize(Reader, root))
				{
					TSharedPtr<FJsonObject>systemInfo = root->GetObjectField("SystemInfo");
					TArray<TSharedPtr<FJsonValue>>homes = root->GetArrayField("Home");
					systemInfo->TryGetBoolField("leftHand", sceneSystemInfo.leftHand);
					systemInfo->TryGetNumberField("version", sceneSystemInfo.version);
					systemInfo->TryGetStringField("up", sceneSystemInfo.up);
					systemInfo->TryGetStringField("unit", sceneSystemInfo.unit);

				
					for (TSharedPtr<FJsonValue>it:homes)
					{
						FHome hometmp;
						TSharedPtr<FJsonObject>tmp=it->AsObject();
						tmp->TryGetStringField("style", hometmp.style);
						TArray<TSharedPtr<FJsonValue>>rooms=tmp->GetArrayField("room");
						for (TSharedPtr<FJsonValue>roomit:rooms)
						{
							FRoom roomtmp;
							TSharedPtr<FJsonObject>datatmp = roomit->AsObject();
							datatmp->TryGetStringField("roomID", roomtmp.roomID);		
							datatmp->TryGetStringArrayField("additions", roomtmp.additions);
							hometmp.room.Add(roomtmp);
						}

						TArray<TSharedPtr<FJsonValue>>meshes=tmp->GetArrayField("Mesh");
						for (TSharedPtr<FJsonValue>meshit: meshes)
						{
							TSharedPtr<FJsonObject>datatmp = meshit->AsObject();
							FMesh meshtmp;
							datatmp->TryGetStringField("guid", meshtmp.guid);
							datatmp->TryGetStringField("name", meshtmp.name);
							datatmp->TryGetStringField("suffix", meshtmp.suffix);
							datatmp->TryGetStringField("currentMaterial", meshtmp.currentMaterial);
							datatmp->TryGetStringArrayField("materialList", meshtmp.materialList);
							datatmp->TryGetStringArrayField("meshList", meshtmp.meshList);
							datatmp->TryGetStringField("roomID", meshtmp.roomID);
							datatmp->TryGetNumberField("saleType", meshtmp.saleType);
							datatmp->TryGetStringField("meshType", meshtmp.meshType);

							if (GetModelFromLocal(meshtmp.guid,meshtmp.suffix))
							{
								meshtmp.Mesh = Meshes;
							}
							

							TArray<TSharedPtr<FJsonValue>>position = datatmp->GetArrayField("position");
							TArray<TSharedPtr<FJsonValue>>rotation = datatmp->GetArrayField("rotation");
							TArray<TSharedPtr<FJsonValue>>scale = datatmp->GetArrayField("scale");
							if (position.Num()==3)
							{
								//ptmp->TryGetNumberField("pos", meshtmp.position.X)
								double datatmp;
								TSharedPtr<FJsonValue> tmp = position[0];
								tmp->TryGetNumber(datatmp);
								meshtmp.position.X = datatmp;

								tmp = position[1];
								tmp->TryGetNumber(datatmp);
								meshtmp.position.Y = datatmp;

								tmp = position[2];
								tmp->TryGetNumber(datatmp);
								meshtmp.position.Z = datatmp;
							}

							if (rotation.Num() == 3)
							{
								//ptmp->TryGetNumberField("pos", meshtmp.position.X)
								double datatmp;
								TSharedPtr<FJsonValue> tmp = rotation[0];
								tmp->TryGetNumber(datatmp);
								meshtmp.rotation.X = datatmp;

								tmp = rotation[1];
								tmp->TryGetNumber(datatmp);
								meshtmp.rotation.Y = datatmp;

								tmp = rotation[2];
								tmp->TryGetNumber(datatmp);
								meshtmp.rotation.Z = datatmp;
							}

							if (scale.Num() == 3)
							{
								//ptmp->TryGetNumberField("pos", meshtmp.position.X)
								double datatmp;
								TSharedPtr<FJsonValue> tmp = scale[0];
								tmp->TryGetNumber(datatmp);
								meshtmp.scaler.X = datatmp;

								tmp = scale[1];
								tmp->TryGetNumber(datatmp);
								meshtmp.scaler.Y = datatmp;

								tmp = scale[2];
								tmp->TryGetNumber(datatmp);
								meshtmp.scaler.Z = datatmp;
							}
								
							hometmp.mesh.Add(meshtmp);

						}

						tmp->TryGetStringArrayField("Material", hometmp.Material);//材质列表


						TArray<TSharedPtr<FJsonValue>>lights = tmp->GetArrayField("Light");
						for(TSharedPtr<FJsonValue> lightit:lights)
						{
							TSharedPtr<FJsonObject>datatmpl = lightit->AsObject();
							FBHPLight lighttmp;

							datatmpl->TryGetStringField("guid", lighttmp.guid);
							datatmpl->TryGetStringField("name", lighttmp.name);
							datatmpl->TryGetStringField("type", lighttmp.type);
							TArray<TSharedPtr<FJsonValue>>position = datatmpl->GetArrayField("position");
							TArray<TSharedPtr<FJsonValue>>rotation = datatmpl->GetArrayField("rotation");
							TArray<TSharedPtr<FJsonValue>>scale = datatmpl->GetArrayField("scale");
							TArray<TSharedPtr<FJsonValue>>target = datatmpl->GetArrayField("target");
							TArray<TSharedPtr<FJsonValue>>color = datatmpl->GetArrayField("color");
							if (position.Num() == 3)
							{
								//ptmp->TryGetNumberField("pos", meshtmp.position.X)
								double datatmp;
								TSharedPtr<FJsonValue> tmp = position[0];
								tmp->TryGetNumber(datatmp);
								lighttmp.position.X = datatmp;

								tmp = position[1];
								tmp->TryGetNumber(datatmp);
								lighttmp.position.Y = datatmp;

								tmp = position[2];
								tmp->TryGetNumber(datatmp);
								lighttmp.position.Z = datatmp;
							}

							if (rotation.Num() == 3)
							{
								//ptmp->TryGetNumberField("pos", meshtmp.position.X)
								double datatmp;
								TSharedPtr<FJsonValue> tmp = rotation[0];
								tmp->TryGetNumber(datatmp);
								lighttmp.rotation.X = datatmp;

								tmp = rotation[1];
								tmp->TryGetNumber(datatmp);
								lighttmp.rotation.Y = datatmp;

								tmp = rotation[2];
								tmp->TryGetNumber(datatmp);
								lighttmp.rotation.Z = datatmp;
							}

							if (scale.Num() == 3)
							{
								//ptmp->TryGetNumberField("pos", meshtmp.position.X)
								double datatmp;
								TSharedPtr<FJsonValue> tmp = scale[0];
								tmp->TryGetNumber(datatmp);
								lighttmp.scale.X = datatmp;

								tmp = scale[1];
								tmp->TryGetNumber(datatmp);
								lighttmp.scale.Y = datatmp;

								tmp = scale[2];
								tmp->TryGetNumber(datatmp);
								lighttmp.scale.Z = datatmp;
							}
							if (target.Num() == 3)
							{
								//ptmp->TryGetNumberField("pos", meshtmp.position.X)
								double datatmp;
								TSharedPtr<FJsonValue> tmp = target[0];
								tmp->TryGetNumber(datatmp);
								lighttmp.target.X = datatmp;

								tmp = target[1];
								tmp->TryGetNumber(datatmp);
								lighttmp.target.Y = datatmp;

								tmp = target[2];
								tmp->TryGetNumber(datatmp);
								lighttmp.target.Z = datatmp;
							}

							if (color.Num() == 4)
							{
								//ptmp->TryGetNumberField("pos", meshtmp.position.X)
								double datatmp;
								TSharedPtr<FJsonValue> tmp = color[0];
								tmp->TryGetNumber(datatmp);
								lighttmp.color.X = datatmp;

								tmp = color[1];
								tmp->TryGetNumber(datatmp);
								lighttmp.color.Y = datatmp;

								tmp = color[2];
								tmp->TryGetNumber(datatmp);
								lighttmp.color.Z = datatmp;

								tmp = color[3];
								tmp->TryGetNumber(datatmp);
								lighttmp.color.W = datatmp;
							}

							datatmpl->TryGetNumberField("angle", lighttmp.angle);
							datatmpl->TryGetNumberField("length", lighttmp.length);
							datatmpl->TryGetNumberField("width", lighttmp.width);
							datatmpl->TryGetNumberField("strength", lighttmp.strength);

							hometmp.light.Add(lighttmp);
						}

						//tmp->TryGetArrayField("room", rooms);

						sceneHomes.Add(hometmp);
					}

					//GetLoaclModel(filePath);
				}
			
			}
			catch (const std::exception&)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		
		

		
	}

	if (GetAllModelFromLocal())
	{
		return true;
	}
	else
	{
		return false;

	}
	
}

bool UBHPScene::ImportSceneFromNet(FString filePath)
{
	return true;
}

bool UBHPScene::GetAllModelFromLocal()
{
	/*for (FHome homeitem:sceneHomes)
	{



		for (size_t i = 0; i < homeitem.mesh.Num(); i++)
		{
			//meshitem.guid
			/*if (GetModelFromLocal(homeitem.mesh[i].guid))
			{
				meshitem.Mesh = Meshes;
			}
			else
			{
				continue;
			}
		}
		

	}*/

	return true;
}

bool UBHPScene::GetModelFromLocal(FString guid,FString suffix)
{
	FString filePath;
	filePath = FPaths::ProjectDir() / TEXT("Scenes")/TEXT("Mesh") ;

	if (!FPaths::DirectoryExists(filePath))//路径不存在则创建
	{
		//FPaths::ge
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*filePath);
	}

	filePath =filePath/guid + "."+ suffix;
	if (!(FPaths::FileExists(filePath)))
	{
		
		if (DownloadModel(guid))
		{
			GetModelFromLocal(guid,suffix);
		}
		else
		{
			FString str = TEXT("模型文件不存在，导入失败:") + filePath;
			BHPLogger::Error(str, 1);
			return false;
		}
		
	}

	if (ParseModelFromFile(filePath))
	{
		return true;
	}
	else {
		return false;
	}

	



	
}

bool UBHPScene::DownloadAllModel()
{
	return false;
}

bool UBHPScene::DownloadModel(FString guid)
{
	return false;

}

bool UBHPScene::GetLocalMat(FString guid)
{
	return false;
}

bool UBHPScene::DownloadRemoteMat(FString guid)
{
	return false;
}

bool UBHPScene::ParseModelFromFile(FString filePath)
{
	if (!(FPaths::FileExists(filePath)))
	{
		FString str = TEXT("模型文件不存在，导入失败:") + filePath;
		BHPLogger::Error(str, 1);
		return false;
	}
	else
	{

		//FString str("aaaa");
		/*const TCHAR* msg = filePath.GetCharArray().GetData();
		int num = filePath.GetAllocatedSize();
		TArray<char> str;
		str.SetNum(num*2);
		char* chars = new char[num*2];

		FPlatformString::Convert(chars, filePath.GetAllocatedSize()*2,msg, filePath.GetAllocatedSize());
		
		FTCHARToUTF8_Convert::Convert(chars, filePath.GetAllocatedSize(),msg, filePath.GetAllocatedSize());
		FString tmp= WCHAR_TO_TCHAR(filePath);*/
		const wchar_t* s1 = *filePath;

		int LenW = wcslen(s1);
		int LenC = LenW * 2;

		//先转换为 char*, 比如 protobuf 不支持 wchar_t，那么可以将中文转换为char，然后储存在protobuf内部。
		char* buf = new char[LenC + 1]();
		memcpy(buf, s1, LenC);

		//验证char*能否还原为 wchar_t 数组
		wchar_t* buf2 = new wchar_t[LenC / 2 + 1]();
		memcpy(buf2, buf, LenC);

		std::string file = TCHAR_TO_UTF8(*filePath);
		//aiString file=
		Assimp::Importer mImporter;
		Assimp::IOSystem ;
		//WideCharToMultiByte(CP_ACP, 0, Source, LengthWM1 + 1, Dest, LengthA, NULL, NULL);
		//ASSIMP_API::utf

		const aiScene* mScenePtr = mImporter.ReadFile(file, aiProcess_Triangulate | aiProcess_MakeLeftHanded | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals );//| aiProcess_FlipUVs | aiProcess_OptimizeMeshes

		if (mScenePtr == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("读取文件失败，请检查格式或者数据是否损坏\n"));
			FString str = TEXT("读取文件失败，请检查格式或者数据是否损坏\n") + filePath;
			BHPLogger::Error(str, 10);
			return false;
		}
		else
		{

			bool result = processNode(mScenePtr->mRootNode, mScenePtr);
			//bool result = processNode2(mScenePtr);
			return result;
		}


	}

}

bool UBHPScene::ImportModelFromNet(FString file)
{
	return true;
}

void UBHPScene::FindMesh(const aiScene* scene, aiNode* node)
{
	FindMeshInfo(scene, node);

	for (uint32 m = 0; m < node->mNumChildren; ++m)
	{
		FindMesh(scene, node->mChildren[m]);
	}
	
}

void UBHPScene::FindMeshInfo(const aiScene* scene, aiNode* node)
{
	for (uint32 i = 0; i < node->mNumMeshes; i++)
	{
		std::string TestString = node->mName.C_Str();
		FString Fs = FString(TestString.c_str());
		UE_LOG(LogTemp, Warning, TEXT("FindMeshInfo. %s\n"), *Fs);
		int meshidx = *node->mMeshes;
		aiMesh *mesh = scene->mMeshes[meshidx];
		FBHPMesh &mi = Meshes[meshidx];

		//transform.
		aiMatrix4x4 tempTrans = node->mTransformation;
		FMatrix tempMatrix;
		tempMatrix.M[0][0] = tempTrans.a1; tempMatrix.M[0][1] = tempTrans.b1; tempMatrix.M[0][2] = tempTrans.c1; tempMatrix.M[0][3] = tempTrans.d1;
		tempMatrix.M[1][0] = tempTrans.a2; tempMatrix.M[1][1] = tempTrans.b2; tempMatrix.M[1][2] = tempTrans.c2; tempMatrix.M[1][3] = tempTrans.d2;
		tempMatrix.M[2][0] = tempTrans.a3; tempMatrix.M[2][1] = tempTrans.b3; tempMatrix.M[2][2] = tempTrans.c3; tempMatrix.M[2][3] = tempTrans.d3;
		tempMatrix.M[3][0] = tempTrans.a4; tempMatrix.M[3][1] = tempTrans.b4; tempMatrix.M[3][2] = tempTrans.c4; tempMatrix.M[3][3] = tempTrans.d4;
		mi.RelativeTransform = FTransform(tempMatrix);

		//vet
		for (uint32 j = 0; j < mesh->mNumVertices; ++j)
		{
			FVector vertex = FVector(
				mesh->mVertices[j].x,
				mesh->mVertices[j].y,
				mesh->mVertices[j].z);

			vertex = mi.RelativeTransform.TransformFVector4(vertex);
			mi.Vertices.Push(vertex);

			//Normal
			if (mesh->HasNormals())
			{
				FVector normal = FVector(
					mesh->mNormals[j].x,
					mesh->mNormals[j].y,
					mesh->mNormals[j].z);

				//normal = mi.RelativeTransform.TransformFVector4(normal);
				mi.Normals.Push(normal);
			}
			else
			{
				mi.Normals.Push(FVector::ZeroVector);
			}

			//UV Coordinates - inconsistent coordinates
			if (mesh->HasTextureCoords(0))
			{
				FVector2D uv = FVector2D(mesh->mTextureCoords[0][j].x, -mesh->mTextureCoords[0][j].y);
				mi.UV0.Add(uv);
			}

			//Tangent
			if (mesh->HasTangentsAndBitangents())
			{
				FProcMeshTangent meshTangent = FProcMeshTangent(
					mesh->mTangents[j].x,
					mesh->mTangents[j].y,
					mesh->mTangents[j].z
				);
				mi.Tangents.Push(meshTangent);
			}

			//Vertex color
			if (mesh->HasVertexColors(0))
			{
				FLinearColor color = FLinearColor(
					mesh->mColors[0][j].r,
					mesh->mColors[0][j].g,
					mesh->mColors[0][j].b,
					mesh->mColors[0][j].a
				);
				mi.VertexColors.Push(color);
			}

		}
	}

}


bool UBHPScene::processNode2(const aiScene* mScenePtr)
{
	if (mScenePtr->HasMeshes())
	{
		Meshes.SetNum(mScenePtr->mNumMeshes, false);

		FindMesh(mScenePtr, mScenePtr->mRootNode);

		for (uint32 i = 0; i < mScenePtr->mNumMeshes; ++i)
		{
			Meshes[i].Index = i;
			//Triangle number
			for (uint32 l = 0; l < mScenePtr->mMeshes[i]->mNumFaces; ++l)
			{
				for (uint32 m = 0; m < mScenePtr->mMeshes[i]->mFaces[l].mNumIndices; ++m)
				{
					Meshes[i].Indices.Push(mScenePtr->mMeshes[i]->mFaces[l].mIndices[m]);
				}
			}
		}

		return true;
	}
	else
	{
		return false;
	}

}

bool UBHPScene::processNode(const aiNode* node, const aiScene* sceneObjPtr)
{
	if (!node || !sceneObjPtr)
	{
		return false;
	}
	// 先处理自身结点
	for (size_t i = 0; i < node->mNumMeshes; ++i)
	{
		// 注意node中的mesh是对sceneObject中mesh的索引
		const aiMesh* meshPtr = sceneObjPtr->mMeshes[node->mMeshes[i]];
		if (meshPtr)
		{
			FBHPMesh meshObj;
			meshObj.Name = meshPtr->mName.C_Str();

			aiMatrix4x4 tempTrans = node->mTransformation;
			FMatrix tempMatrix;
			tempMatrix.M[0][0] = tempTrans.a1; tempMatrix.M[0][1] = tempTrans.b1; tempMatrix.M[0][2] = tempTrans.c1; tempMatrix.M[0][3] = tempTrans.d1;
			tempMatrix.M[1][0] = tempTrans.a2; tempMatrix.M[1][1] = tempTrans.b2; tempMatrix.M[1][2] = tempTrans.c2; tempMatrix.M[1][3] = tempTrans.d2;
			tempMatrix.M[2][0] = tempTrans.a3; tempMatrix.M[2][1] = tempTrans.b3; tempMatrix.M[2][2] = tempTrans.c3; tempMatrix.M[2][3] = tempTrans.d3;
			tempMatrix.M[3][0] = tempTrans.a4; tempMatrix.M[3][1] = tempTrans.b4; tempMatrix.M[3][2] = tempTrans.c4; tempMatrix.M[3][3] = tempTrans.d4;
			meshObj.RelativeTransform = FTransform(tempMatrix);
			meshObj.Index = i;
	
			BHPLogger::Info(meshObj.Name, 1);
			if (processMesh(meshPtr, sceneObjPtr, meshObj))
			{
				Meshes.Add(meshObj);
			}
		}
	}
	// 处理子结点
	for (size_t i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], sceneObjPtr);
	}
	return true;
}
bool UBHPScene::processMesh(const aiMesh* meshPtr, const aiScene* sceneObjPtr, FBHPMesh& meshObj)
{
	if (!meshPtr || !sceneObjPtr)
	{
		return false;
	}
	
	// 从Mesh得到顶点数据、法向量、纹理数据
	TArray<FVector> vertex;
	TArray<FVector2D> UV;
	TArray<FVector> normals;
	TArray<int32> indics;
	for (size_t i = 0; i < meshPtr->mNumVertices; ++i)
	{
		FVector Vertmp,normaltmp;
		FVector2D UVtmp;
		// 获取顶点位置
		if (meshPtr->HasPositions())
		{
			Vertmp.X = meshPtr->mVertices[i].x;
			Vertmp.Y = meshPtr->mVertices[i].y;
			Vertmp.Z = meshPtr->mVertices[i].z;
		}
		Vertmp = meshObj.RelativeTransform.TransformFVector4(Vertmp);
		vertex.Push(Vertmp);

		// 获取纹理数据 目前只处理0号纹理
		if (meshPtr->HasTextureCoords(0))
		{
			UVtmp.X = meshPtr->mTextureCoords[0][i].x;
			UVtmp.Y = meshPtr->mTextureCoords[0][i].y;
		}
		else
		{
			UVtmp.X = 0.0f;
			UVtmp.Y = 0.0f;
		}		
		UV.Push(UVtmp);


		// 获取法向量数据
		if (meshPtr->HasNormals())
		{
			normaltmp.X = meshPtr->mNormals[i].x;
			normaltmp.Y = meshPtr->mNormals[i].y;
			normaltmp.Z = meshPtr->mNormals[i].z;
		}
		normals.Push(normaltmp);
	}

	meshObj.Vertices = vertex;
	meshObj.UV0 = UV;
	meshObj.Normals = normals;

	// 获取索引数据
	for (size_t i = 0; i < meshPtr->mNumFaces; ++i)
	{
		aiFace face = meshPtr->mFaces[i];
		if (face.mNumIndices != 3)
		{
			//std::cerr << "Error:Model::processMesh, mesh not transformed to triangle mesh." << std::endl;
			BHPLogger::Error(TEXT("模型解析错误,模型没有三角化"),3);
			return false;
		}
		for (size_t j = 0; j < face.mNumIndices; ++j)
		{
			indics.Push(face.mIndices[j]);
		}
	}
	meshObj.Indices = indics;


	//Tangent
	if (meshPtr->HasTangentsAndBitangents())
	{
		FProcMeshTangent meshTangent = FProcMeshTangent(
			meshPtr->mTangents->x,
			meshPtr->mTangents->y,
			meshPtr->mTangents->z		
		);
		meshObj.Tangents.Push(meshTangent);
	}

	//Vertex color
	if (meshPtr->HasVertexColors(0))
	{
		 
		FLinearColor color = FLinearColor(
			meshPtr->mColors[0]->r,
			meshPtr->mColors[0]->g,
			meshPtr->mColors[0]->b,
			meshPtr->mColors[0]->a
		);
		meshObj.VertexColors.Push(color);
	}

	// 获取纹理数据
	if (meshPtr->mMaterialIndex >= 0)
	{
		const aiMaterial* materialPtr = sceneObjPtr->mMaterials[meshPtr->mMaterialIndex];
		// 获取diffuse类型
		TArray<FBHPTexture> diffuseTexture;
		processMaterial(materialPtr, sceneObjPtr, aiTextureType_DIFFUSE, diffuseTexture);
		//textures.insert(textures.end(), diffuseTexture.begin(), diffuseTexture.end());
		// 获取specular类型
		TArray<FBHPTexture> specularTexture;
		processMaterial(materialPtr, sceneObjPtr, aiTextureType_SPECULAR, specularTexture);
		//textures.insert(textures.end(), specularTexture.begin(), specularTexture.end());
	}
	
	return true;
}
/*
* 获取一个材质中的纹理
*/
bool UBHPScene::processMaterial(const aiMaterial* matPtr, const aiScene* sceneObjPtr,
	const aiTextureType textureType, TArray<FBHPTexture>& textures)
{
	

	if (!matPtr
		|| !sceneObjPtr)
	{
		return false;
	}
	/*if (matPtr->GetTextureCount(textureType) <= 0)
	{
		return true;
	}*/
	for (size_t i = 0; i < matPtr->GetTextureCount(textureType); ++i)
	{
		FBHPTexture text;
		aiString textPath;
		aiReturn retStatus = matPtr->GetTexture(textureType, i, &textPath);
		if (retStatus != aiReturn_SUCCESS
			|| textPath.length == 0)
		{
			/*std::cerr << "Warning, load texture type=" << textureType
				<< "index= " << i << " failed with return value= "
				<< retStatus << std::endl;*/
			continue;
		}
		/*std::string absolutePath = this->modelFileDir + "/" + textPath.C_Str();
		LoadedTextMapType::const_iterator it = this->loadedTextureMap.find(absolutePath);
		if (it == this->loadedTextureMap.end()) // 检查是否已经加载过了
		{
			GLuint textId = TextureHelper::load2DTexture(absolutePath.c_str());
			text.id = textId;
			text.path = absolutePath;
			text.type = textureType;
			textures.push_back(text);
			loadedTextureMap[absolutePath] = text;
		}
		else
		{
			textures.push_back(it->second);
		}*/
	}
	return true;
}