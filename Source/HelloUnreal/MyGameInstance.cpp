// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"	   //해당 cpp의 header 파일은 언제나 최상위에

#include "Card.h"
#include "Person.h"
#include "Staff.h"
#include "Student.h"
#include "Teacher.h"
UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("Default School");
}

void UMyGameInstance::Init()
{
	Super::Init();
	TArray<UPerson*> Persons = {NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>()};
	for (const auto Person : Persons)
	{
		const UCard* OwnCard = Person->GetCard();
		check(OwnCard);
		ECardType CardType = OwnCard->GetCardType();

		UE_LOG(LogTemp, Log, TEXT("Person Type = %s  Card Type  = %d"), *Person->GetName(), CardType);

		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/HelloUnreal.ECardType"));
		if (CardEnumType)
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64) CardType).ToString();
			UE_LOG(LogTemp, Log, TEXT("Person Type = %s  Card Type  = %s"), *Person->GetName(), *CardMetaData);
		}

	}
}
