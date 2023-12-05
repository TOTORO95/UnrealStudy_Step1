// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"	   //해당 cpp의 header 파일은 언제나 최상위에

#include "Student.h"
#include "StudentManager.h"
void CheckUObjecttIsVaild(const UObject* InObject, const FString& InTag)
{

	if (InObject->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] Vaild Unreal Object"), *InTag);	
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] UnVaild Unreal Object"), *InTag);	
	}
}

void CheckUObjecttIsNull(const UObject* InObject, const FString& InTag)
{
	if (InObject == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] nullptr Unreal Object"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] not nulltpr Unreal Object"), *InTag);
	}
}
void UMyGameInstance::Init()
{
	Super::Init();
	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	NonPropStudents.Add(NewObject<UStudent>());
	PropStudents.Add(NewObject<UStudent>());
	StudentManager = new FStudentManager(NewObject<UStudent>());
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	const UStudent* UStudentInManager = StudentManager->GetStudent();
	delete StudentManager;
	StudentManager = nullptr; 

	CheckUObjecttIsNull(UStudentInManager, TEXT("UStudentInManager"));
	CheckUObjecttIsVaild(UStudentInManager, TEXT("UStudentInManager"));

	CheckUObjecttIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjecttIsVaild(NonPropStudent, TEXT("NonPropStudent"));
	
	CheckUObjecttIsNull(PropStudent, TEXT("PropStudent"));
	CheckUObjecttIsVaild(PropStudent, TEXT("PropStudent"));

	CheckUObjecttIsNull(NonPropStudents[0], TEXT("NonPropStudents"));
	CheckUObjecttIsVaild(NonPropStudents[0], TEXT("NonPropStudents"));

	CheckUObjecttIsNull(PropStudents[0], TEXT("PropStudents"));
	CheckUObjecttIsVaild(PropStudents[0], TEXT("PropStudents"));
}
