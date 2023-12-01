// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"

UTeacher::UTeacher()
{
	Name = TEXT("Default Teacher Name");
	Year = 3;
}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("Teaching...  %s"), *GetName());
}
