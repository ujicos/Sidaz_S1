#include "stdafx.h"

const byte moveax1ret[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 };
byte hasdlcbackup[ARRAYSIZE(moveax1ret)];
bool DLCUnlocker::FirstRun = true;

typedef char(__fastcall* tProcessDLC)(__int64 ID, int amount, __int64 prob_size, __int64 a4);
tProcessDLC ProcessDLC = (tProcessDLC)0x1404BD360; //Updated to AW

void DLCUnlocker::SetHasDLC(bool to)
{
	if (FirstRun)
	{
		Utils::ReadAddy(0x1405396F0, hasdlcbackup, ARRAYSIZE(moveax1ret)); //Updated to AW.
	}
	Utils::PatchAddy(0x1405396F0, to ? (byte*)moveax1ret : (byte*)hasdlcbackup, ARRAYSIZE(moveax1ret)); //Updated to AW.
	FirstRun = false;
}

void DLCUnlocker::SetDLCUnlock(bool to)
{
	SetHasDLC(to);
	
	if(!to)
		*(int*)0x14B31CE1C = 1; //Updated to AW.

	ProcessDLC(259250, 1, 16, 16843008);
	ProcessDLC(259251, 1, 32, 63214797);
	ProcessDLC(259252, 1, 64, 63214800);
	ProcessDLC(259253, 1, 128, 63214798);
	ProcessDLC(286635, 1, 2048, 63214800);
	ProcessDLC(286636, 1, 4096, 63214799);

	
}

void DLCUnlocker::UnlockDLCUnlocks()
{
	Utils::PatchAddy(0x140563DD0, (byte*)moveax1ret, ARRAYSIZE(moveax1ret)); //Updated to AW.
}
