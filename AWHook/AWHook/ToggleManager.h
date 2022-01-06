
#pragma once
class SidazToggles
{
public:
	bool HostMenu = false;
	bool ModMenu = false;
	bool menuaw = false;
	bool bring[18];
	float EBRADIUS;

	bool DLCUnlock = false;
	float ebradius = 250.0f;

	bool UFO[18];
	bool EB[18];
	bool OldUFO[18];
	bool freeze[18];
	bool depatch = true;
	bool depatchbonz;

	bool TA[18];
	bool TA_LimitWeapons[18];
	bool TA_IgnoreAim[18];

	bool GodMode[18];

	float TA_FOV[18];

	Vector SavedPositions[18];
	bool SpawnSaved[18];

	int CurGameType = 0;
	int CurMap = 0;

	void HandleKeys(WPARAM param);
	void Init();

	int MaxPlayers = 12;
	bool SetMaxPlayers = false;

	bool ChangeName = false;

	float CurTimescale = 1.0f;
	float oldTimeScale = 1.0f;

	bool HeadshotSlowmo = false;

	bool Bot_Changename = false;
	bool Bot_NoKick = false;
	bool Bot_Think = true;

	int Team_Selected = 0;

	std::string BotName = "";

	std::string NameToChange = "";
};

extern SidazToggles Toggles;