// Copyright Robot Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SAVEMANAGER_API USaveBase : public USaveGame
{
	GENERATED_BODY()

public:

	/**
	 * Override this function to initialize save when it runs for the first time.
	 */
	virtual void FirstRunInit();
	
	/**
	 * Override this function to implement migration logic.
	 * It is called when the game updates and existing save files need to be changed or fixed.
	 *
	 * This function should handle recursive migrations between multiple versions.
	 * For example, upgrading from version 2 to 5 may look like this:
	 *
	 * @code
	 * MigrateFromVersion(2)
	 * {
	 *     // 2 -> 3
	 *     MigrateFromVersion(3)
	 *     {
	 *         // 3 -> 4
	 *         MigrateFromVersion(4)
	 *         {
	 *             // 4 -> 5
	 *         }
	 *     }
	 * }
	 * @endcode
	 *
	 * @param OldVersion The version number of the save file before migration.
	 */
	virtual void MigrateFromVersion(int32 OldVersion);

	UPROPERTY()
	class USaveManagerGameInstanceSubsystem* GameInstance = nullptr;
	
	/**
	 * If true, no code will be written to the slot, but it will be written globally.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Config", meta = (ToolTip = "If true, no code will be written to the slot, but it will be written globally."))
	bool bPreventSaveToSlot = false;
};