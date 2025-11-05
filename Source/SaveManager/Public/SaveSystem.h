// Copyright Robot Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SaveBase.h"
#include "SaveSystem.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMANAGER_API USaveSystem : public UObject
{
	GENERATED_BODY()

	protected:
	USaveBase* LoadOrCreateSaveGameObject(UClass* ObjectClass, bool &bOutFirstRun);
	void SaveGameSaveObject(USaveBase* SaveObject);

	virtual void PostInitProperties() override;
	virtual void BeginDestroy() override;

	UPROPERTY()
	TMap<TSubclassOf<USaveBase>, USaveBase*> SaveStructs;

	template<typename T>
	void RegisterSaveStruct()
	{
		SaveStructs.Add(T::StaticClass(), nullptr);
	}

	template<typename T1, typename T2, typename ...Ts>
	void RegisterSaveStruct()
	{
		SaveStructs.Add(T1::StaticClass(), nullptr);
		RegisterSaveStruct<T2, Ts...>();
	}

public:
	void Init();
	void Shutdown();

	template<typename T>
	T* GetSave()
	{
		return Cast<T>(GetSave(T::StaticClass()));
	}
	class USaveBase* GetSave(TSubclassOf<USaveBase> ObjectClass);

	template<typename T>
	void Save()
	{
		Save(T::StaticClass());
	}
	void Save(TSubclassOf<USaveBase> ObjectClass);
	void SaveAll();

	template<typename T>
	void Load()
	{
		Load(T::StaticClass());
	}
	void Load(TSubclassOf<USaveBase> ObjectClass);
	void LoadAll();

	template<typename T>
	void Reset()
	{
		Reset(T::StaticClass());
	}
	void Reset(TSubclassOf<USaveBase> ObjectClass);
	void ResetAll();

	static USaveSystem* Get();

	UPROPERTY()
	class USaveManagerGameInstanceSubsystem* GameInstance = nullptr;

protected:
	static USaveSystem* Singleton;

	TArray<TSubclassOf<USaveBase>> GeneralSave;
};
