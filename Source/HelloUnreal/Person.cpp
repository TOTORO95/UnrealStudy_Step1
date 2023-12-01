// Fill out your copyright notice in the Description page of Project Settings.

#include "Person.h"

UPerson::UPerson()
{
	Name = TEXT("Kim JunYoung");
	Year = 1;
}

const FString& UPerson::GetName() const
{
	return Name;
}
void UPerson::SetName(const FString& InName)
{
	Name = InName;
}