// Copyright Robot Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveSystemStatics.generated.h"

class USaveBase;

UCLASS()
class SAVEMANAGER_API USaveSystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Load all saves */
	UFUNCTION(BlueprintCallable, Category = "Tomentor Save System")
	static void LoadAll();

	/** Save all saves */
	UFUNCTION(BlueprintCallable, Category = "Tomentor Save System")
	static void SaveAll();

	/** Reset all saves */
	UFUNCTION(BlueprintCallable, Category = "Tomentor Save System")
	static void ResetAll();

	/** Load a specific save class */
	UFUNCTION(BlueprintCallable, Category = "Tomentor Save System")
	static void LoadByClass(TSubclassOf<USaveBase> SaveClass);

	/** Save a specific save class */
	UFUNCTION(BlueprintCallable, Category = "Tomentor Save System")
	static void SaveByClass(TSubclassOf<USaveBase> SaveClass);

	/** Reset a specific save class */
	UFUNCTION(BlueprintCallable, Category = "Tomentor Save System")
	static void ResetByClass(TSubclassOf<USaveBase> SaveClass);

	/** Get a specific save class instance */
	UFUNCTION(BlueprintPure, Category = "Tomentor Save System")
	static USaveBase* GetSaveByClass(TSubclassOf<USaveBase> SaveClass);
};
