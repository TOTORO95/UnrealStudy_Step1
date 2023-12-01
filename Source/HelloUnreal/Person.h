// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Person.generated.h"

/**
 *
 */
UCLASS()
class HELLOUNREAL_API UPerson : public UObject
{
	GENERATED_BODY()
public:
	UPerson();
	FORCEINLINE const FString& GetName() const;
	FORCEINLINE void SetName(const FString& InName);

protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;

private:
};
