// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Engine.h"
#include "Game/BHPMeshActor.h"
//#include "BHPUtil.generated.h"
#include <string>
#include <locale>
#include <codecvt>

#include "BHPUtil.generated.h"


// string的编码方式为utf8，则采用：
namespace BHPStrConvert {
	FORCEINLINE std::string wstring2utf8string(const std::wstring& str)
	{
		static std::wstring_convert<std::codecvt_utf8<wchar_t> > strCnv;
		return strCnv.to_bytes(str);
	}

	FORCEINLINE std::wstring utf8string2wstring(const std::string& str)
	{
		static std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
		return strCnv.from_bytes(str);
	}

	// string的编码方式为除utf8外的其它编码方式，可采用：
	FORCEINLINE std::string wstring2string(const std::wstring& str, const std::string& locale)
	{
		typedef std::codecvt_byname<wchar_t, char, std::mbstate_t> F;
		static std::wstring_convert<F> strCnv(new F(locale));

		return strCnv.to_bytes(str);
	}

	FORCEINLINE std::wstring string2wstring(const std::string& str, const std::string& locale)
	{
		typedef std::codecvt_byname<wchar_t, char, std::mbstate_t> F;
		static std::wstring_convert<F> strCnv(new F(locale));

		return strCnv.from_bytes(str);
	}

}

namespace BHPLogger {

	FORCEINLINE void Debug(FString msg, float time)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, time, FColor::Yellow, msg);
	}

	FORCEINLINE void Error(FString msg, float time)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, time, FColor::Red, msg);
	}

	FORCEINLINE void Info(FString msg, float time)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, time, FColor::Green, msg);
	}

}


/**
 * 
 */

UCLASS()
class BIMHOUSEPLAYER_API UBHPUtil : public UObject
{
	GENERATED_BODY()
		
		
public:

	
	   

	
};
