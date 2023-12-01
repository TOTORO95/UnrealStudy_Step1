// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MyGameInstance.generated.h"

/**
 *
 */
UCLASS()
class HELLOUNREAL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();
	virtual void Init() override;

private:
	UPROPERTY()	   // 를 선언함으로써 리플렉션을 통해 런타임이든 컴파일이든 얻기위해 사용
	FString SchoolName;
};
