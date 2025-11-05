// Copyright Robot Games. All Rights Reserved.


#include "SaveManager/Structures/SaveGameVersioning.h"

#include "SaveManagerSettings.h"
#include "SaveSystem.h"

static int32 GetConfigSaveVersion()
{
	return GetDefault<USaveManagerSettings>()->SaveVersion;
}

void USaveGameVersioning::FirstRunInit()
{
	SetSaveVersion(GetConfigSaveVersion());
}

void USaveGameVersioning::MigrateFromVersion(const int32 OldVersion)
{
	if (const int32 CurrentVersion = GetConfigSaveVersion(); OldVersion < CurrentVersion)
	{
		SetSaveVersion(CurrentVersion);
	}
}

int32 USaveGameVersioning::GetSaveVersion() const
{
	return SaveVersion;
}

void USaveGameVersioning::SetSaveVersion(const int32 NewSaveVersion, const bool bSave/*= true*/)
{
	SaveVersion = NewSaveVersion;
	if (bSave)
	{
		USaveSystem::Get()->Save<USaveGameVersioning>();
	}
}
