// Fill out your copyright notice in the Description page of Project Settings.

#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	Contents = TEXT("Default School Info");
}

void UCourseInfo::ChangedCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
	Contents = InNewContents;
	UE_LOG(LogTemp, Log, TEXT("[CourseInfo] Changed School Info Broadcast!!"));
	OnChanged.Broadcast(InSchoolName, Contents);
}
