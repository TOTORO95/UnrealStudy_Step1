// Fill out your copyright notice in the Description page of Project Settings.

#include "Student.h"

#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("Default Student Name");
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("Studying...  %s"), *GetName());
}

void UStudent::GetNotification(const FString& School, const FString& NewCourseInfo)
{
	UE_LOG(
		LogTemp, Log, TEXT("[Student] A Message that %s received from %s == MessageInfo %s"), *GetName(), *School, *NewCourseInfo);
}
