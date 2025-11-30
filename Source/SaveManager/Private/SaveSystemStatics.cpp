// Copyright Robot Games. All Rights Reserved.

#include "SaveSystemStatics.h"
#include "SaveSystem.h"
#include "SaveBase.h"
#include "UObject/UObjectIterator.h"

void USaveSystemStatics::LoadAll()
{
	USaveSystem::Get()->LoadAll();
}

void USaveSystemStatics::SaveAll()
{
	USaveSystem::Get()->SaveAll();
}

void USaveSystemStatics::ResetAll()
{
	USaveSystem::Get()->ResetAll();
}

void USaveSystemStatics::LoadByClass(TSubclassOf<USaveBase> SaveClass)
{
	if (SaveClass)
	{
		USaveSystem::Get()->Load(SaveClass);
	}
}

void USaveSystemStatics::SaveByClass(TSubclassOf<USaveBase> SaveClass)
{
	if (SaveClass)
	{
		USaveSystem::Get()->Save(SaveClass);
	}
}

void USaveSystemStatics::ResetByClass(TSubclassOf<USaveBase> SaveClass)
{
	if (SaveClass)
	{
		USaveSystem::Get()->Reset(SaveClass);
	}
}

USaveBase* USaveSystemStatics::GetSaveByClass(TSubclassOf<USaveBase> SaveClass)
{
	if (!SaveClass)
		return nullptr;

	return USaveSystem::Get()->GetSave(SaveClass);
}

void USaveSystemStatics::SetSaveSlotIndex(const int32 NewSlot)
{
	USaveSystem::Get()->SetSaveSlot(NewSlot);
}

int32 USaveSystemStatics::GetSaveSlotIndex()
{
	return USaveSystem::Get()->GetSaveSlot();
}