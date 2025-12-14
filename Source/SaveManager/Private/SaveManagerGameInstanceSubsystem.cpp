// Author: Robot 12


#include "SaveManagerGameInstanceSubsystem.h"

#include "SaveSystem.h"

void USaveManagerGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	SaveSystem = NewObject<USaveSystem>(this);
	SaveSystem->GameInstance = this;
	SaveSystem->Init();
}
