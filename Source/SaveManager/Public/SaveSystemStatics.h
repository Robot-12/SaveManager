// Copyright Robot Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveManager/Structures/SaveSlotBase.h"
#include "SaveSystemStatics.generated.h"

class USaveBase;

UCLASS()
class SAVEMANAGER_API USaveSystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Load all saves */
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Load all saves"), Category = "Save System")
	static void LoadAll();

	/** Save all saves */
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Save all saves"), Category = "Save System")
	static void SaveAll();

	/** Reset all saves */
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Reset all saves"), Category = "Save System")
	static void ResetAll();

	/** Load a specific save class */
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Load a specific save class"), Category = "Save System")
	static void LoadByClass(TSubclassOf<USaveBase> SaveClass);

	/** Save a specific save class */
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Save a specific save class"), Category = "Save System")
	static void SaveByClass(TSubclassOf<USaveBase> SaveClass);

	/** Reset a specific save class */
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Reset a specific save class"), Category = "Save System")
	static void ResetByClass(TSubclassOf<USaveBase> SaveClass);

	/** Get a specific save class instance */
	UFUNCTION(BlueprintPure, Category = "Save System", meta = (DeterminesOutputType = "SaveClass", ToolTip = "Get a specific save class instance"))
	static USaveBase* GetSaveByClass(TSubclassOf<USaveBase> SaveClass);
	
	/** Sets the active slot */
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Sets the active slot"), Category = "Save System")
	static void SetSaveSlotIndex(int32 NewSlot);
	
	/** Get the active slot */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (ToolTip = "Get the active slot"), Category = "Save System")
	static int32 GetSaveSlotIndex();
};