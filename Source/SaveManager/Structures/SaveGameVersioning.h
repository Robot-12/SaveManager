// Author: Robot 12

#pragma once

#include "CoreMinimal.h"
#include "SaveBase.h"
#include "SaveGameVersioning.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMANAGER_API USaveGameVersioning : public USaveBase
{
	GENERATED_BODY()

public:
	USaveGameVersioning();
	
	virtual void FirstRunInit() override;
	virtual void MigrateFromVersion(int32 OldVersion) override;

	UFUNCTION(BlueprintPure, Category = "Save|Versioning")
	int32 GetSaveVersion() const;

	void SetSaveVersion(int32 NewSaveVersion, bool bSave = true);

private:
	UPROPERTY(EditAnywhere, Category = Basic)
	int32 SaveVersion = 0;
};
