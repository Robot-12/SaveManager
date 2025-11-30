// Copyright Robot Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SaveBase.h"
#include "SaveSlotBase.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMANAGER_API USaveSlotBase : public USaveBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Set Slot Name"), Category = "Slot System")
		void SetSlotName(FName NewSlotName);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (ToolTip = "Get Slot Name"), Category = "Slot System")
		FName GetSlotName() const;
	
private:
	UPROPERTY()
		FName SlotName;
};