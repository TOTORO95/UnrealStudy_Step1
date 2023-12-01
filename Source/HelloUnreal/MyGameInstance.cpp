// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"	   //해당 cpp의 header 파일은 언제나 최상위에

#include "Card.h"
#include "Person.h"
#include "Staff.h"
#include "Student.h"
#include "Teacher.h"
#include "CourseInfo.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("Uneral School");
}

void UMyGameInstance::Init()
{
	Super::Init();
	CourseInfo = NewObject<UCourseInfo>(this);//Outer를 해당 인스턴스로 셋팅함으로써 has-a관계 성립

	TArray<UStudent*> Persons = {NewObject<UStudent>(), NewObject<UStudent>(), NewObject<UStudent>()};
	
	for (int32 i = 0; i < Persons.Num(); i++)
	{
		FString NewName = TEXT("Student");
		NewName.AppendInt(i);
		Persons[i]->SetName(NewName);
		CourseInfo->OnChanged.AddUObject(Persons[i], &UStudent::GetNotification);
	}
	CourseInfo->ChangedCourseInfo(SchoolName, TEXT("Changed CourseInfo!!!"));
}
