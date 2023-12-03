// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"	   //해당 cpp의 header 파일은 언제나 최상위에

#include "Algo/Accumulate.h"
#include "Card.h"
#include "CourseInfo.h"
#include "Person.h"
#include "Staff.h"
#include "Student.h"
#include "Teacher.h"

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
}
