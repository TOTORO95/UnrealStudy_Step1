// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"	   //해당 cpp의 header 파일은 언제나 최상위에

#include "Student.h"
#include "JsonObjectConverter.h"

void UMyGameInstance::Init()
{
	Super::Init();
	FStudentData RawDataSrc(28, TEXT("Kim JunYoung"));

	const FString SaveDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Log, TEXT("Save File Directory = %s"), *SaveDir);

	{
		const FString RawDataFileName(TEXT("RawData.bin"));
		FString RawDataAbsolutePath = FPaths::Combine(*SaveDir, *RawDataFileName);
		UE_LOG(LogTemp, Log, TEXT("Save File All Directory RawDataAbsolutePath= %s"), *RawDataAbsolutePath);
		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		UE_LOG(LogTemp, Log, TEXT("Change File All Directory = %s"), *RawDataAbsolutePath);
		FArchive* RAwFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);
		if (RAwFileWriterAr)
		{
			*RAwFileWriterAr << RawDataSrc;
			RAwFileWriterAr->Close();
			delete RAwFileWriterAr;
			RAwFileWriterAr = nullptr;
		}

		FStudentData RawDataDest;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
		if (RawFileReaderAr)
		{
			*RawFileReaderAr << RawDataDest;
			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;
		}
		UE_LOG(LogTemp, Log, TEXT("Change File All Directory = %s"), *RawDataAbsolutePath);
		UE_LOG(LogTemp, Log, TEXT("[RawData]  Name = %s, Order %d"), *RawDataDest.Name, RawDataDest.Order);
	}

	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetOrder(29);
	StudentSrc->SetName(TEXT("JY"));
	{
		const FString& ObjectDataFileName(TEXT("ObjectData.bin"));
		FString ObjectDataAbsolutPath = FPaths::Combine(*SaveDir, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsolutPath);

		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriter(BufferArray);
		StudentSrc->Serialize(MemoryWriter);
		TUniquePtr<FArchive> FileWriterAr(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutPath));
		if (FileWriterAr)
		{
			*FileWriterAr << BufferArray;
			FileWriterAr->Close();
		}

		TArray<uint8> BufferArrayFromFile;
		TUniquePtr<FArchive> FileReaderAr(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutPath));
		if (FileReaderAr)
		{
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();
		}

		FMemoryReader MemoryReaderAr(BufferArrayFromFile);
		UStudent* StudentDest = NewObject<UStudent>();
		StudentDest->Serialize(MemoryReaderAr);
		PrintStudentInfo(StudentDest, TEXT("ObjectData"));
	}

	{ // Json
		const FString JsonDataFileName(TEXT("StudentJsonData.txt"));
		FString JsonDataAbsolutePath = FPaths::Combine(*SaveDir, *JsonDataFileName);
		FPaths::MakeStandardFilename(JsonDataAbsolutePath);

		TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();
		FJsonObjectConverter::UStructToJsonObject(StudentSrc->GetClass(), StudentSrc, JsonObjectSrc); // Object -> Json 변환

		FString JsonOutString;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr(TJsonWriterFactory<TCHAR>::Create(&JsonOutString));
		if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
		{
			FFileHelper::SaveStringToFile(JsonOutString, *JsonDataAbsolutePath);
		}
		
		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath);
		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr(TJsonReaderFactory<TCHAR>::Create(JsonInString));

		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			UStudent* JsonStudentDest = NewObject<UStudent>();
			if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest))
			{
				PrintStudentInfo(JsonStudentDest, TEXT("JsonData"));
			}
		}
	}


}

void UMyGameInstance::PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] Name = %s, Order = %d"), *InTag, *(InStudent->GetName()), InStudent->GetOrder());
}
