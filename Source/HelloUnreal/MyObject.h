// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"			// 언리얼 오브젝트가 되기위해 필요한 기본적인 헤더 
#include "UObject/NoExportTypes.h"	// 언리얼 오브젝트가 되기위해 필요한 기본적인 헤더
#include "MyObject.generated.h"		//MyObject.generated.h 라는 파일은 에디터에서는 보이지않지만 프로젝트 내부의 다른 디렉토리에 들어가있음


UCLASS() //언리얼 오브젝트 선언임을 알리기위해 UClASS() 매크로를 명시
/*
	HELLOUNREAL_API 매크로를 사용하면 현재 오브젝트가 다른 DLL, Module 언리얼의 라이브러리 단위에서
	해당 클래스를 참조하지 않게된다.
	반대로 해당 매크로를 사용하지않으면 다른 라이브러리에서 해당 클래스를 참조하게 된다.
*/ 
class HELLOUNREAL_API UMyObject : public UObject
{
	GENERATED_BODY()
	
};
