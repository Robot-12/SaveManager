// Copyright Robot Games. All Rights Reserved.


#include "SaveSlotBase.h"

void USaveSlotBase::SetSlotName(const FName NewSlotName)
{
	SlotName = NewSlotName;
}

FName USaveSlotBase::GetSlotName() const
{
	return SlotName;
}
