// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentManager.h"
#include "Student.h"
FStudentManager::FStudentManager(UStudent* InStudent) : SafeStudent(InStudent)
{
}

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
	if (SafeStudent->IsValidLowLevel())
	{
		Collector.AddReferencedObject(SafeStudent);
	}
}

FString FStudentManager::GetReferencerName() const
{
	return TEXT("FStudnetManager");
}
