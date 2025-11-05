// Copyright Robot Games. All Rights Reserved.


#include "SaveSystem.h"

#include "Kismet/GameplayStatics.h"
#include "SaveManager/Structures/SaveGameVersioning.h"

USaveSystem* USaveSystem::Singleton = nullptr;

USaveSystem* USaveSystem::Get()
{
	checkf(Singleton != nullptr, TEXT("SaveSystem used before init!"));
	return Singleton;
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
	// Register every new save class here!
	// RegisterSaveStruct<
	// 	USaveGameVersioning
	// >();

	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* Class = *It;
		if (Class->IsChildOf(USaveBase::StaticClass()) && !Class->HasAnyClassFlags(CLASS_Abstract))
		{
			SaveStructs.Add(Class, nullptr);
		}
	}
	
	// Always load all saves so they will be ready to use.
	LoadAll();

	// Run save migration
	int32 LoadedSaveVersion = GetSave<USaveGameVersioning>()->GetSaveVersion();
	
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
		SaveAll(); // save after the migration
	}
}

void USaveSystem::Shutdown()
{

}

USaveBase* USaveSystem::LoadOrCreateSaveGameObject(UClass* ObjectClass, bool &bOutFirstRun)
{
	USaveBase* ObjectInstance = nullptr;

	//const bool bIsGeneral = GeneralSave.Contains(ObjectClass);

	FString SlotName;
	SlotName = "Tor_" + ObjectClass->GetName();

	// if (bIsGeneral)
	// {
	// }
	// else
	// {
	// 	SlotName = StaticEnum<ESaveType>()->GetNameStringByValue((int64)SaveType) + "_" + ObjectClass->GetName();
	// }

	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		ObjectInstance = Cast<USaveBase>(
			UGameplayStatics::LoadGameFromSlot(SlotName, 0)
		);
	}
	else if (UGameplayStatics::DoesSaveGameExist(ObjectClass->GetName(), 0))
	{
		ObjectInstance = Cast<USaveBase>(UGameplayStatics::LoadGameFromSlot(ObjectClass->GetName(), 0));
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

void USaveSystem::SaveGameSaveObject(USaveBase* SaveObject)
{
	if (SaveObject)
	{
		//const bool bIsGeneral = GeneralSave.Contains(SaveObject->GetClass());

		FString SlotName;
		SlotName = "SM_" + SaveObject->GetClass()->GetName();

		// if (bIsGeneral)
		// {
		// }
		// else
		// {
		// 	SlotName = StaticEnum<ESaveType>()->GetNameStringByValue((int64)SaveType) 
		// 			 + "_" + SaveObject->GetClass()->GetName();
		// }

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
