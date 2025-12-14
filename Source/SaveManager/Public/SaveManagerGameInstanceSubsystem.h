// Author: Robot 12

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManagerGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SAVEMANAGER_API USaveManagerGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY()
	class USaveSystem* SaveSystem = nullptr;
	
};