// Copyright Robot Games. All Rights Reserved.


#include "SaveBase.h"

void USaveBase::FirstRunInit()
{
	// Override this function to initialize save when it runs for the first time.
}

void USaveBase::MigrateFromVersion(int32 OldVersion)
{
	// Override this function to implement migration. It will be used
	// when game updates and save files must be changed/fixed.
	// Do a recurse migration when switching between multiple versions.
	// Example: Upgrate from version 2 to 5.
	// MigrateFromVersion(2)
	// {
	//   Do migration from 2->3.
	//   MigrateFromVersion(3)
	//   {
	//     Do migration from 3->4.
	//     MigrateFromVersion(4)
	//     {
	//       Do migration from 4->5
	//     }
	//   }
	// }
}
