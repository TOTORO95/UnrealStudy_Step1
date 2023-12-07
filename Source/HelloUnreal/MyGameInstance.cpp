// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"	   //해당 cpp의 header 파일은 언제나 최상위에

#include "Student.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"
const FString UMyGameInstance::PackageName(TEXT("/Game/Student")); // /Game <- Game에서 사용되는 에셋들을 모아둔 대표 경로
const FString UMyGameInstance::AssetName(TEXT("TopStudent")); // 

void PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] Name = %s, Order = %d"), *InTag, *(InStudent->GetName()), InStudent->GetOrder());
}


UMyGameInstance::UMyGameInstance()
{
	const FString TopSoftObjectPath(FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName));
	static ConstructorHelpers::FObjectFinder<UStudent> UAsset_TopStudent(*TopSoftObjectPath);
	if (UAsset_TopStudent.Succeeded())
	{
		PrintStudentInfo(UAsset_TopStudent.Object, TEXT("Constructor"));
	}
}

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
	StudentSrc->SetOrder(25);
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

	SaveStudentPackage();
	//LoadStudentPackage();
	//LoadStudentObject();

	// 비동기 로딩
	const FString TopSoftObjectPath(FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName));
	Handle = StreamableManager.RequestAsyncLoad(TopSoftObjectPath, [&]() {
		if (Handle.IsValid() && Handle->HasLoadCompleted())
		{
			UStudent* TopStudent = Cast<UStudent>(Handle->GetLoadedAsset());
			if (TopStudent)
			{			
				PrintStudentInfo(TopStudent, TEXT("ASync Laod"));
				Handle->ReleaseHandle();
				Handle.Reset();
				
			}
		}
	});
}




void UMyGameInstance::SaveStudentPackage() const
{
	UPackage* StudentPackage(::LoadPackage(nullptr, *PackageName, LOAD_None));
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}

	StudentPackage = CreatePackage(*PackageName);
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;
	
	UStudent* TopStudent = NewObject<UStudent>(StudentPackage,UStudent::StaticClass(), *AssetName, ObjectFlag);
	TopStudent->SetName(TEXT("KJY"));
	TopStudent->SetOrder(29);

	const int32 NumOfSubs = 10;
	for (int32 Idx = 1; Idx <= NumOfSubs; ++Idx)
	{
		FString SubObjectName = FString::Printf(TEXT("Student%d"),Idx);
		UStudent* SubStudent = NewObject<UStudent>(TopStudent, UStudent::StaticClass(), *SubObjectName, ObjectFlag);
		SubStudent->SetName(FString::Printf(TEXT("Student%d"),Idx));
		SubStudent->SetOrder(Idx);
	}
	const FString PackageFileName(FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()));
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;
	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp, Log, TEXT("Suceess Save Package "));
	}

}

void UMyGameInstance::LoadStudentPackage() const
{
	UPackage* StudentPackage(::LoadPackage(nullptr, *PackageName, LOAD_None));

	if (StudentPackage == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Not Found Package File"));
		return;
	}

	StudentPackage->FullyLoad(); //찾은 패키지의 리소스를 모두 로딩하는 함수
	const UStudent* TopStudent = FindObject<UStudent>(StudentPackage, *AssetName);
	PrintStudentInfo(TopStudent, TEXT("FindObject"));

}

void UMyGameInstance::LoadStudentObject() const
{
	const FString TopSoftObjectPath(FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName));
	UStudent* TopStudent(LoadObject<UStudent>(nullptr, *TopSoftObjectPath));
	if (TopStudent)
	{
		PrintStudentInfo(TopStudent, TEXT("LoadStudentObject"));
	}
	
}
