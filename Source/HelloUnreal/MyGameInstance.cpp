// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("Default School");
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("===================="));
	UClass* ClassRunTime(GetClass());
	UClass* ClassComptileTime(UMyGameInstance::StaticClass());
	//check(ClassRunTime != ClassComptileTime);
	ensure(ClassRunTime != ClassComptileTime);
	ensureMsgf(ClassRunTime != ClassComptileTime, TEXT("일단 넣어봄"));

	UE_LOG(LogTemp, Log, TEXT("Class Name = %s"), *ClassRunTime->GetName());
	UE_LOG(LogTemp, Log, TEXT("Default School Name = %s"), *ClassRunTime->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("===================="));
}
