// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MyGameInstance.generated.h"

/**
 *
 */
USTRUCT()
struct FStudentData
{
	GENERATED_BODY()
	FStudentData()
	{
		Name = TEXT("Kim Junyoung");
		Order = -1;
	}
	FStudentData(FString InName, int32 InOrder) : Name(InName), Order(InOrder)
	{
	}

	bool operator==(const FStudentData& InOther) const
	{
		return Order == InOther.Order;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

UCLASS()
class HELLOUNREAL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();
	virtual void Init() override;

private:
	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;

	UPROPERTY()	   // 를 선언함으로써 리플렉션을 통해 런타임이든 컴파일이든 얻기위해 사용
	FString SchoolName;

	TArray<FStudentData> StudentDatas;

	UPROPERTY() // 아래처럼 언리얼 오브젝트를 TArray로 다룰때에는 반드시 사용
	TArray<TObjectPtr<class UStudent>> Students;

	TMap<int32, FString> StudentMap;
};
