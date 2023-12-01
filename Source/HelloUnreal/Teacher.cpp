// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"

UTeacher::UTeacher()
{
	Name = TEXT("Default Teacher Name");
	Year = 3;
	Id = 2;
}

void UTeacher::DoLesson()
{
	Super::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%d Years ID = %d Name = %s // Teacher do Lesson"), Year, Id, *Name);
}
