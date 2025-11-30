// Copyright Robot Games. All Rights Reserved.


#include "SaveSystem.h"

#include "SaveManagerSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SaveManager/Structures/SaveGameVersioning.h"

USaveSystem* USaveSystem::Singleton = nullptr;

USaveSystem* USaveSystem::Get()
{
	checkf(Singleton != nullptr, TEXT("SaveSystem used before init!"));
	return Singleton;
}

static FString GetConfigPrefixFile()
{
	return GetDefault<USaveManagerSettings>()->PrefixFile;
}

static FString GetConfigPrefixFolder()
{
	return GetDefault<USaveManagerSettings>()->PrefixFolder;
}

TSubclassOf<USaveSlotBase> USaveSystem::GetSaveSlotClass()
{
	if (GetDefault<USaveManagerSettings>()->SaveSlotClass)
	{
		return GetDefault<USaveManagerSettings>()->SaveSlotClass;
	}
	else
	{
		return USaveSlotBase::StaticClass();
	}
}

void USaveSystem::PostInitProperties()
{
	Super::PostInitProperties();
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		checkf(Singleton == nullptr, TEXT("There can be only one SaveSystem!"));
		Singleton = this;
	}
}

void USaveSystem::BeginDestroy()
{
	Singleton = nullptr;
	Super::BeginDestroy();
}

void USaveSystem::Init()
{
	const UClass* ActiveSlotClass = GetSaveSlotClass();

	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* Class = *It;
		FString ClassName = Class->GetName();

		if (ClassName.StartsWith("SKEL_") || ClassName.StartsWith("REINST_"))
		{
			continue;
		}

		if (Class->IsChildOf(USaveBase::StaticClass()) && !Class->HasAnyClassFlags(CLASS_Abstract))
		{
			if (Class->IsChildOf(USaveSlotBase::StaticClass()))
			{
				if (Class == ActiveSlotClass)
				{
					SaveStructs.Add(Class, nullptr);
				}
			}
			else
			{
				SaveStructs.Add(Class, nullptr);
			}
		}
	}
    
	LoadAll();

	const int32 LoadedSaveVersion = GetSave<USaveGameVersioning>()->GetSaveVersion();
    
	if (LoadedSaveVersion == 0)
	{
		ResetAll();
	}
	for (auto& SaveStruct : SaveStructs)
	{
		SaveStruct.Value->MigrateFromVersion(LoadedSaveVersion);
	}
	if (LoadedSaveVersion < GetSave<USaveGameVersioning>()->GetSaveVersion())
	{
		SaveAll(); 
	}
}

USaveBase* USaveSystem::LoadOrCreateSaveGameObject(const UClass* ObjectClass, bool& bOutFirstRun) const
{
	USaveBase* ObjectInstance = nullptr;
	const USaveBase* DefaultObject = Cast<USaveBase>(ObjectClass->GetDefaultObject());

	FString SlotName = GetConfigPrefixFile() + ObjectClass->GetName();
	FString AltSlotName = ObjectClass->GetName();


	if (SaveSlot != -1 && !DefaultObject->bPreventSaveToSlot)
	{
		FString FolderName = GetConfigPrefixFolder() + FString::FromInt(SaveSlot);
		SlotName = FPaths::Combine(FolderName, SlotName);
		AltSlotName = FPaths::Combine(FolderName, AltSlotName);
	}

	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		ObjectInstance = Cast<USaveBase>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	}
	else if (UGameplayStatics::DoesSaveGameExist(AltSlotName, 0))
	{
		ObjectInstance = Cast<USaveBase>(UGameplayStatics::LoadGameFromSlot(AltSlotName, 0));
	}

	if (ObjectInstance == nullptr)
	{
		bOutFirstRun = true;
		ObjectInstance = NewObject<USaveBase>(GetTransientPackage(), ObjectClass);
	}
	else
	{
		bOutFirstRun = false;
	}

	return ObjectInstance;
}

void USaveSystem::SaveGameSaveObject(USaveBase* SaveObject) const
{
	if (SaveObject)
	{
		FString SlotName = GetConfigPrefixFile() + SaveObject->GetClass()->GetName();

		if (SaveSlot != -1 && !SaveObject->bPreventSaveToSlot)
		{
			FString FolderName = GetConfigPrefixFolder() + FString::FromInt(SaveSlot);

			if (const FString FullSavePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("SaveGames"), FolderName); !IFileManager::Get().DirectoryExists(*FullSavePath))
			{
				IFileManager::Get().MakeDirectory(*FullSavePath, true);
			}

			SlotName = FPaths::Combine(FolderName, SlotName);
		}

		UGameplayStatics::SaveGameToSlot(SaveObject, SlotName, 0);
	}
}

USaveBase* USaveSystem::GetSave(TSubclassOf<USaveBase> ObjectClass)
{
	if (USaveBase** SaveStruct = SaveStructs.Find(ObjectClass))
	{
		return *SaveStruct;
	}
	else
	{
		return nullptr;
	}
}

void USaveSystem::Save(TSubclassOf<USaveBase> ObjectClass)
{
	if (USaveBase* SaveStruct = GetSave(ObjectClass))
	{
		SaveGameSaveObject(SaveStruct);
	}
}

void USaveSystem::SaveAll()
{
	for (auto SaveStruct : SaveStructs)
	{
		SaveGameSaveObject(SaveStruct.Value);
	}
}

void USaveSystem::Load(TSubclassOf<USaveBase> ObjectClass)
{
	bool bFirstRun = false;
	if (USaveBase* LoadedSaveGame = LoadOrCreateSaveGameObject(ObjectClass, bFirstRun))
	{
		SaveStructs[ObjectClass] = LoadedSaveGame;
		SaveStructs[ObjectClass]->GameInstance = GameInstance;
		if (bFirstRun)
		{
			SaveStructs[ObjectClass]->FirstRunInit();
		}
	}
}

void USaveSystem::LoadAll()
{
	for (auto& SaveStruct : SaveStructs)
	{
		bool bFirstRun = false;
		if (USaveBase* LoadedSaveGame = LoadOrCreateSaveGameObject(SaveStruct.Key, bFirstRun))
		{
			SaveStruct.Value = LoadedSaveGame;
			SaveStruct.Value->GameInstance = GameInstance;
			if (bFirstRun)
			{
				SaveStruct.Value->FirstRunInit();
			}
		}
	}
}

void USaveSystem::Reset(TSubclassOf<USaveBase> ObjectClass)
{
	if (SaveStructs.Contains(ObjectClass))
	{
		SaveStructs[ObjectClass] = NewObject<USaveBase>(GetTransientPackage(), ObjectClass);
		SaveStructs[ObjectClass]->GameInstance = GameInstance;
		SaveStructs[ObjectClass]->FirstRunInit();
	}
}

void USaveSystem::ResetAll()
{
	// Copy all classes first. Just want to be sure that new objects pointers will
	// be stored to the correct place while iterating.
	TArray<TSubclassOf<USaveBase>> ObjectClassList;
	for (auto SaveStruct : SaveStructs)
	{
		ObjectClassList.Add(SaveStruct.Key);
	}
	for (TSubclassOf<USaveBase> ObjectClass : ObjectClassList)
	{
		Reset(ObjectClass);
	}
	SaveAll();
}

//Slots System

TMap<int32, USaveSlotBase*> USaveSystem::GetAvailableSaveSlots()
{
	TMap<int32, USaveSlotBase*> LoadedSlots;
	TArray<FString> FoundFolders;

	const UClass* SlotClass = GetSaveSlotClass();
	if (!SlotClass)
	{
		return LoadedSlots;
	}

	const FString SearchPath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("SaveGames"), TEXT("*"));
	IFileManager::Get().FindFiles(FoundFolders, *SearchPath, false, true);

	const FString FileBaseName = GetConfigPrefixFile() + SlotClass->GetName();
	const FString FolderPrefix = GetConfigPrefixFolder();

	for (const FString& FolderName : FoundFolders)
	{
		if (FolderName.StartsWith(FolderPrefix))
		{
			FString SlotIdString = FolderName;
			SlotIdString.RightChopInline(FolderPrefix.Len());

			if (SlotIdString.IsNumeric())
			{
				const int32 SlotID = FCString::Atoi(*SlotIdString);
				const FString SlotPath = FPaths::Combine(FolderName, FileBaseName);

				if (UGameplayStatics::DoesSaveGameExist(SlotPath, 0))
				{
					USaveBase* LoadedGame = Cast<USaveBase>(UGameplayStatics::LoadGameFromSlot(SlotPath, 0));

					if (USaveSlotBase* SlotObject = Cast<USaveSlotBase>(LoadedGame))
					{
						LoadedSlots.Add(SlotID, SlotObject);
					}
				}
			}
		}
	}

	return LoadedSlots;
}

void USaveSystem::SetSaveSlot(const int32 NewSlot)
{
	SaveSlot = NewSlot;
}

int32 USaveSystem::GetSaveSlot() const
{
	return SaveSlot;
}