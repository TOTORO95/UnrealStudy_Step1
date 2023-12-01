// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"	   //해당 cpp의 header 파일은 언제나 최상위에

#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("Default School");
}

void UMyGameInstance::Init()
{
	Super::Init();
	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };
	for (const auto Person : Persons)
	{
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		FString CastResult = TEXT("Unable");
		if (LessonInterface)
		{
			CastResult = TEXT("Enable");
		}

		UE_LOG(LogTemp, Log, TEXT("%s class Type = %s "), *CastResult, *Person->GetName());
	}
}
