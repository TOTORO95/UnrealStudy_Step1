// Fill out your copyright notice in the Description page of Project Settings.

#include "Student.h"

UStudent::UStudent()
{
	Name = TEXT("Default Student Name");
	Year = 1;
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("Studying...  %s"), *GetName());
}
