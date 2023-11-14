// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("Hello World literal"));

	TCHAR ChArr[] = TEXT("Hello World chArr");
	UE_LOG(LogTemp, Log, ChArr);

	FString TextStr = ChArr;
	UE_LOG(LogTemp, Log, TEXT("%s"), *TextStr);

	FString logStr = TEXT("Log fString");
	const TCHAR* longCharArray = *logStr;

	FString unrealText = TEXT("Unreal Engine");
	TCHAR logCharArr[] = TEXT("TCHAR Array Text");
	FString LogCharString = unrealText;

	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();
	TCHAR logCharArrayWithSize[100];
	FCString::Strcpy(logCharArrayWithSize, LogCharString.Len(), LogCharDataPtr);

	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
	{
		int32 Index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
		FString EndString = LogCharString.Mid(Index);
		UE_LOG(LogTemp, Log, TEXT("Find Text : %s "), *EndString);
	}

	FString LeftStr, RightStr;
	if (LogCharString.Split(TEXT(" "), &LeftStr, &RightStr))
	{
		UE_LOG(LogTemp, Log, TEXT("Sucess Split Text Left = %s 와 Right = %s"), *LeftStr, *RightStr);
		UE_LOG(LogTemp, Log, TEXT("LiveCoindg Sucess Split Text Left = %s 와 Right = %s"), *LeftStr, *RightStr);
	}

	int32 IntValue = 32;
	float FloatValue = 3.141592;

	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(IntValue);

	UE_LOG(LogTemp, Log, TEXT("%s"), *(FString::Printf(TEXT("Int = %d Float = %f"), IntValue, FloatValue)));
	UE_LOG(LogTemp, Log, TEXT("Int = %s Float = %s"), *IntString, *FloatString);

	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);
	FString FloatIntString2 = FString::Printf(TEXT("Int = %d Float = %f "), IntValueFromString, FloatValueFromString);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString2);

	FName key1(TEXT("ITEM"));
	FName key2(TEXT("item"));
	UE_LOG(LogTemp, Log, TEXT("Fname Compare Result = %s"), key1 == key2 ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Log, TEXT("Live Coding Test 5:27"));
	UE_LOG(LogTemp, Log, TEXT("Live Coding Test 5:32"));
}