// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MyGameInstance.generated.h"

/**
 *
 */

struct FStudentData
{
	FStudentData()
	{
	}
	FStudentData(int32 InOrder, const FString& InName) : Order(InOrder), Name(InName)
	{
	}
	friend FArchive& operator<<(FArchive& Ar, FStudentData& InStudentData)
	{
		Ar << InStudentData.Order;
		Ar << InStudentData.Name;
		return Ar;
	}
	int32 Order = -1;
	FString Name = TEXT("Default Name");
};

UCLASS()
class HELLOUNREAL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	void PrintStudentInfo(const class UStudent* InStudent, const FString& InTag);

private:
	TObjectPtr<class UStudent> StudentSrc;
};
