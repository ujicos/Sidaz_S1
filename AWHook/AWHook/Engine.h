#pragma once





class SimEngine
{
public:

	typedef void(__fastcall* tLiveStorage_PlayerDataSetIntByName)(int localClientNum, short name, int value);
	tLiveStorage_PlayerDataSetIntByName LiveStorage_PlayerDataSetIntByName = (tLiveStorage_PlayerDataSetIntByName)0x00000001403BF550;

	__int64(*SL_GetString)(const char* str, unsigned int user) = (__int64(*)(const char*, unsigned int))0x00000001403F1440;

	typedef void(__fastcall* tSV_FastRestart)(int localClientNum);
	tSV_FastRestart SV_FastRestart = (tSV_FastRestart)0x1404374E0;

	//int* LocalPlayer = (int*)0x14155757C;


	bool IsAlive(void* ent)
	{
		return GetHealth(ent) > 0;
	}

	int GetHealth(void* ent)
	{
		return *(int*)((DWORD_PTR)ent + (0x14155757C * 0x5758));
	}

	void* GetEntity(int entnum)
	{
		return (void*)(0x144758C70 + (0x2E0 * entnum));
	}
};

extern SimEngine Engine;