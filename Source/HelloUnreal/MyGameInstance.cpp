// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"	   //해당 cpp의 header 파일은 언제나 최상위에

#include "Student.h"
#include "Teacher.h"

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
	// check(ClassRunTime != ClassComptileTime);
	ensure(ClassRunTime != ClassComptileTime);
	ensureMsgf(ClassRunTime != ClassComptileTime, TEXT("일단 넣어봄"));

	UE_LOG(LogTemp, Log, TEXT("Class Name = %s"), *ClassRunTime->GetName());
	UE_LOG(LogTemp, Log, TEXT("Default School Name = %s"), *ClassRunTime->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("===================="));

	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();
	Student->SetName(TEXT("Student Kim"));
	UE_LOG(LogTemp, Log, TEXT("Change Student Name = %s"), *Student->GetName());

	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp)
	{
		FString CurTeacherName;
		NameProp->GetValue_InContainer(Teacher, &CurTeacherName);
		UE_LOG(LogTemp, Log, TEXT("Current Teacher Name = %s"), *CurTeacherName);

		FString newTeacherName = TEXT("Teacher JY");
		NameProp->SetValue_InContainer(Teacher, &newTeacherName);
		UE_LOG(LogTemp, Log, TEXT("New Teacher Name = %s"), *Teacher->GetName());
	}
	Student->DoLesson();
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}
}
