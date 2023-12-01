// Fill out your copyright notice in the Description page of Project Settings.

#include "Staff.h"

#include "Card.h"

UStaff::UStaff()
{
	Name = TEXT("Default Staff Name");
	Card->SetCardType(ECardType::Staff);
}
