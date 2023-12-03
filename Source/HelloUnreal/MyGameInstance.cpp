// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"	   //해당 cpp의 header 파일은 언제나 최상위에

#include "Algo/Accumulate.h"

FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원영");

	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];
	return RandArray.GetData();
}

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	Super::Init();
	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 Idx = 1; Idx <= ArrayNum; ++Idx)
	{
		Int32Array.Add(Idx);
	}

	Int32Array.RemoveAll([](int32 Val) { return Val % 2 == 0; });

	Int32Array += {2, 4, 6, 8, 10};

	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);
	ensure(Int32Array == Int32ArrayCompare);

	int32 Sum = 0;
	for (int32 Idx = 0; Idx < Int32Array.Num(); ++Idx)
	{
		Sum += Int32Array[Idx];
	}
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(Sum != SumByAlgo);

	TSet<int32> Int32Set;
	for (int32 Idx = 1; Idx <= ArrayNum; ++Idx)
	{
		Int32Set.Add(Idx);
	}

	Int32Set.Remove(6);
	Int32Set.Remove(7);
	Int32Set.Remove(8);
	Int32Set.Remove(9);
	Int32Set.Remove(10);
	Int32Set.Add(6);
	Int32Set.Add(7);
	Int32Set.Add(8);
	Int32Set.Add(9);
	Int32Set.Add(10);

	const int32 StudentNum = 300;
	for (int32 Idx = 0; Idx < StudentNum; ++Idx)
	{
		StudentDatas.Emplace(FStudentData(MakeRandomName(), Idx));
	}

	TArray<FString> AllStudentName;
	Algo::Transform(StudentDatas, AllStudentName, [](const FStudentData& Val) { return Val.Name; });
	UE_LOG(LogTemp, Log, TEXT("All Student Number : %d"), AllStudentName.Num());

	Algo::Transform(StudentDatas, StudentMap, [](const FStudentData& Val) { return TPair<int32, FString>(Val.Order, Val.Name); });
	UE_LOG(LogTemp, Log, TEXT("All Student Map Size: %d"), AllStudentName.Num());

	TMap<FString, int32> StudentsMapUniqueName;
	Algo::Transform( StudentDatas, StudentsMapUniqueName, [](const FStudentData& Val) 
		{ 
			return TPair<FString, int32>(Val.Name, Val.Order); 
		}
	);
	UE_LOG(LogTemp, Log, TEXT("Unique Student Name Map Size: %d"), StudentsMapUniqueName.Num());

	TMultiMap<FString, int32> StudentMapByName;
	Algo::Transform(StudentDatas, StudentMapByName, [](const FStudentData& Val) 
	{ 
		return TPair<FString, int32>(Val.Name, Val.Order);
	});

	UE_LOG(LogTemp, Log, TEXT("Multi Student Name Map Size: %d"), StudentMapByName.Num());

	const FString TagetName(TEXT("이혜은"));
	TArray<int32> AllOrders;
	StudentMapByName.MultiFind(TagetName,AllOrders);
	UE_LOG(LogTemp, Log, TEXT("이혜은 이름의 수 : %d"),  AllOrders.Num());

	TSet<FStudentData> StudentSet;
	for (int32 Idx = 1; Idx < StudentNum; ++Idx)
	{
		StudentSet.Emplace(FStudentData(MakeRandomName(),Idx));
	}
}
