// Author: Robot 12

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SaveManager/Structures/SaveSlotBase.h"
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
	
	/**
	 * Adds a prefix to the save file (Format: Prefix + SaveName).
	 * IMPORTANT: Changing this will prevent older save files from loading unless manually renamed. Recommended to set this early.
	 */
	UPROPERTY(EditAnywhere, Config, Category="Config|Prefix", meta = (ToolTip = "Adds a prefix to the save file (Format: Prefix + SaveName). IMPORTANT: Changing this will prevent older save files from loading unless manually renamed. Recommended to set this early."))
	FString PrefixFile = FString(TEXT("SM_"));

	/**
	 * Adds a prefix to the slot folder where data is stored (Format: Prefix + SlotIndex).
	 * IMPORTANT: Changing this will prevent older slots from loading unless folders are manually renamed. Recommended to set this early.
	 */
	UPROPERTY(EditAnywhere, Config, Category="Config|Prefix", meta = (ToolTip = "Adds a prefix to the slot folder where data is stored (Format: Prefix + SlotIndex). IMPORTANT: Changing this will prevent older slots from loading unless folders are manually renamed. Recommended to set this early."))
	FString PrefixFolder = FString(TEXT("Slot_"));

	/**
	 * Specifies the class used for save slots, containing metadata such as the slot name, thumbnail, and description.
	 */
	UPROPERTY(EditAnywhere, Config, Category="Config", meta = (ToolTip = "Specifies the class used for save slots, containing metadata such as the slot name, thumbnail, and description."))
	TSubclassOf<USaveSlotBase> SaveSlotClass = USaveSlotBase::StaticClass();
};