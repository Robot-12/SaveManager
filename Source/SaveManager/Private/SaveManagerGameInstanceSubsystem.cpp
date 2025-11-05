// Copyright Robot Games. All Rights Reserved.


#include "SaveManagerGameInstanceSubsystem.h"

#include "SaveSystem.h"

void USaveManagerGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	SaveSystem = NewObject<USaveSystem>(this);
	SaveSystem->GameInstance = this;
	SaveSystem->Init();
}
