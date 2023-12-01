// Fill out your copyright notice in the Description page of Project Settings.

#include "Student.h"

UStudent::UStudent()
{
	Name = TEXT("Default Student Name");
	Year = 1;
	Id = 1;
}

void UStudent::DoLesson()
{
	Super::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%d Years ID = %d Name = %s // Student do Lesson"), Year, Id, *Name);
}
