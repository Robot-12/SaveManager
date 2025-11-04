// Copyright Robot Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SaveManagerSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Save Manager"))
class SAVEMANAGER_API USaveManagerSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	USaveManagerSettings()
	{
		CategoryName = TEXT("Plugins");
		SectionName = TEXT("Save Manager");
	}
	
	/** 
	 * Current version of the save system.
	 * Used to detect and migrate data when the save format changes between game versions.
	 * Increase this value whenever you modify how save data is structured.
	 */
	UPROPERTY(EditAnywhere, config, Category="Version",  meta = (ToolTip = "Current version of the save system. Increase this when the save data format changes."))
	int32 SaveVersion = 1;
};
