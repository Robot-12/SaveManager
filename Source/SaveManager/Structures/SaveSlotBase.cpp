// Author: Robot 12


#include "SaveSlotBase.h"

void USaveSlotBase::SetSlotName(const FName NewSlotName)
{
	SlotName = NewSlotName;
}

FName USaveSlotBase::GetSlotName() const
{
	return SlotName;
}
