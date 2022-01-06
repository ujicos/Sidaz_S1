#include "stdafx.h"

byte buf[] = { 0x73, 0x61, 0x79, 0x20, 0x22, 0x5E, 0x02, 0x15, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0x22 };

typedef void(__fastcall* tCbuf_AddText)(int localClientNum, const char *text);
tCbuf_AddText nigger_addtext = (tCbuf_AddText)0x1403F6B50;


void Switch(bool &b)
{
	b = !b;
}

INT GetActionIndex(CONST PCHAR Action)
{
	CONST CHAR** ActionList = (CONST CHAR**)0x001409E3AB0;

	for (INT i = 0; ActionList[i]; i++)
	{
		if (_stricmp(Action, ActionList[i]) == NULL)
		{
			return i;
		}
	}

	return -1;
}



//1443F4600

void SimToggles::HandleKeys(WPARAM param)
{
	if (param == VK_INSERT)
	{
		Switch(HostMenu);
		printf("ya did get called\n");
	}
	else if (param == VK_DELETE)
	{
		Switch(ModMenu);
	}

	if (param == VK_F6)
	{
		
		nigger_addtext(0, ((char*)buf));


	}

	



		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)donac, 0, 0, 0);

		//writeaddy<int>(0x01B11554 + (IW4::MISC::GetHostId() * 0x366C), 0);
		//bots_assignteam();



		//IW4::SV::GameSendServerCommand(IW4::MISC::GetHostId(), IW4::SV::svscmd_type::SV_CMD_CAN_IGNORE, IW4::MISC::va("f \"^1%s UFO Off (F5 to turn On)!\"", IW4::STRUCTS::cg->clients[IW4::MISC::GetHostId()].name));

	



	//printf("commandtime: %i", level_locals->clients.ps.weapState->weaponState);

//	level_locals->clients.ps.weapState[1].weaponState;

	//level_locals->clients.ps.commandTime

	if (param == VK_F7)
	{
		Engine.bg_compassShowEnemies->current.enabled = !Engine.bg_compassShowEnemies->current.enabled;
	}

}

void SimToggles::Init()
{
	memset(UFO, 0, sizeof(bool) * 18);
	memset(OldUFO, 0, sizeof(bool) * 18);

	memset(EB, 0, sizeof(bool) * 18);
	memset(EB_LimitWeapons, 1, sizeof(bool) * 18);
	memset(EB_IGNORE, 0, sizeof(bool) * 18);
	memset(GodMode, 0, sizeof(bool) * 18);
	
	for (int i = 0; i < 18; i++)
		EBRADIUSplayer[i] = 1000;

	for (int i = 0; i < 18; i++)
		SavedPositions[i] = Vector(0, 0, 0);

	memset(SpawnSaved, 0, sizeof(bool) * 18);
}
