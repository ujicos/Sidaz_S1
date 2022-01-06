#include "stdafx.h"
#include "Menu.h"


using namespace ImGui;

float test = 1;



struct playerState_s {
	char __padding000[0x5B8];
	int currentOffhand;
	char __padding001[0x08];
	int currentWeapon;
};

struct gentity_s
{
	char pad_0x0000[0x158]; //0x0000
	playerState_s * client; //0x0158 
	__int64 turret; //0x0160 
	__int64 agent; //0x0168 
	__int64 sentient; //0x0170 
	__int64 vehicle; //0x0178 
	char pad_0x0180[0x8]; //0x0180
	__int16 model; //0x0188 
	unsigned char physicsObject; //0x018A 
	unsigned char takedamage; //0x018B 
	char pad_0x018C[0x44]; //0x018C
	__int32 health; //0x01D0 
	char pad_0x01D4[0x10C]; //0x01D4
};

gentity_s* g_entities = (gentity_s*)0x144758C70;

gentity_s* Scr_GetEntity(int entnum) {
	return &g_entities[entnum];
}


struct ClientClass
{
	std::string Name;
	int Index;
};


std::vector<ClientClass> ClientVec;


int* LocalPlayer = (int*)0x14155757C;

typedef signed __int64(__fastcall* tCL_GetClientName)(int localClientNum, int index, char *buf, int size);
tCL_GetClientName CL_GetClientName = (tCL_GetClientName)0X140213E40;


void AddNameTokens(int i, std::string &nam)
{
	if (Toggles.TA[i] || Toggles.UFO[i] || Toggles.GodMode[i])
	{
		nam += "  [";

		if (Toggles.TA[i])
			nam += " TA";
		if (Toggles.UFO[i])
			nam += " U";
		if (Toggles.GodMode[i])
			nam += " G";

		nam += " ]";
	}
}




void ClearPlayer(int i)
{
	Toggles.TA[i] = false;
	Toggles.UFO[i] = false;
	Toggles.GodMode[i] = false;
	Toggles.TA_IgnoreAim[i] = false;
	Toggles.TA_LimitWeapons[i] = true;
	Toggles.TA_FOV[i] = 180.0f;
	Toggles.SavedPositions[i] = Vector(0, 0, 0);
	Toggles.SpawnSaved[i] = false;
}

void UpdateClientVector()
{
	ClientVec.clear();
	for (int i = 0; i < 18; i++)
	{
		//if (IsPlayer(GetEntity(i)))
		if (g_entities[i].health >= 0)
		{
			char namebuf[128];
			CL_GetClientName(*LocalPlayer, i, namebuf, 127);
			if (namebuf[0] != 0)
			{
				ClientClass t;
				t.Name = std::string(namebuf);
				t.Index = i;
				AddNameTokens(i, t.Name);
				ClientVec.push_back(t);
			}
			else
			{
				ClearPlayer(i);
			}
		}
		else
		{
			ClearPlayer(i);
		}
	}


}


struct ImageStruct_t
{
	// IDirect3DBaseTexture9* pTexture; //0x0004
	ID3D11Resource* pTexture; //0x0000 texture struct goes here
	char pad_0x0008[0x58]; //0x0008
	char* imageName; //0x0060 

}; //Size=0x0068

ImageStruct_t *image;






template <typename T>

void writeAddy(DWORD_PTR address, T value)
{
	DWORD o1, o2;
	VirtualProtect((void*)address, sizeof(T), PAGE_EXECUTE_READWRITE, &o1);
	*(T*)address = value;
	VirtualProtect((void*)address, sizeof(T), o1, &o2);
}

void copyAddy(void* address, void* value, size_t size)
{
	DWORD o1, o2;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &o1);
	memcpy(address, value, size);
	VirtualProtect(address, size, o1, &o2);
}



typedef void(__fastcall* tCbuf_AddTextt)(int localClientNum, const char *text);
tCbuf_AddTextt Cbuf_AddTextt = (tCbuf_AddTextt)0x1403AED70;

void Menu::Render()
{

	//UpdateClientVector();
	ImGui_ImplDX11_NewFrame();

	static bool no_titlebar = false;
	static bool no_border = true;
	static bool no_resize = false;
	static bool auto_resize = false;
	static bool no_move = false;
	static bool no_scrollbar = false;
	static bool no_collapse = false;
	static bool no_menu = true;
	static bool start_pos_set = false;

	//MenuLayoutManager::MW3Layout();

	

	ImGuiWindowFlags	window_flags = 0;
	if (no_titlebar)	window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_resize)		window_flags |= ImGuiWindowFlags_NoResize;
	if (auto_resize)	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	if (no_move)		window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar)	window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)	window_flags |= ImGuiWindowFlags_NoCollapse;
	if (!no_menu)		window_flags |= ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowSize(ImVec2(450, 600), ImGuiSetCond_FirstUseEver);
	if (!start_pos_set) { ImGui::SetNextWindowPos(ImVec2(25, 25)); start_pos_set = true; }

	ImGui::GetIO().MouseDrawCursor = IsOpen;

	if (Toggles.HostMenu)
	{
		//UpdateClientVector();

		ImGui::Begin("uji's AW Azza", &IsOpen, window_flags);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);
		ImGui::PushItemWidth(-140);


		Cbuf_AddTextt(0, "data_validation_enabled 0");

		if (ImGui::CollapsingHeader("Game Settings"))
		{

			if (ImGui::Button("Force Start"))
			{
				writeAddy<int>(0x140B1CA00 + 4, 0);

				Cbuf_AddTextt(0, "party_teambased 0;xblive_privatematch 1;onlinegame 0;xpartygo;xblive_privatematch 0;onlinegame 1;set scr_dm_score_kill 9999999");

				//Cbuf_AddText(0, "party_teambased 0;xblive_privatematch 1;onlinegame 0;");
			}
			if (ImGui::Button("Fast Restart"))
			{
				Engine.SV_FastRestart(*Engine.LocalPlayer);
			}

			ImGui::Checkbox("Bots Think", &Toggles.Bot_Think);

			if (ImGui::Checkbox("Depatch Bounces", &Toggles.depatchbonz))
			{
				Utils::PatchAddy<byte>(0x140229003, Toggles.depatchbonz ? 0x9090 : 0x1575);
			}
			if (ImGui::Checkbox("Depatch Elevators", &Toggles.depatch))
			{
				Utils::PatchAddy<WORD>(0x140142B00, Toggles.depatch ? 0x9090 : 0x0975);
				Utils::PatchAddy<WORD>(0x14014613D, Toggles.depatch ? 0x9090 : 0x6775);
				Utils::PatchAddy<byte>(0x1401461A4, Toggles.depatch ? 0xEB : 0x74);

			}
			if (ImGui::Button("addbot"))
			{
				Cbuf_AddTextt(0, "addtestclient;wait 1;addteam;wait 1;addclass");
			}


			if (ImGui::Button("Derank"))
			{
				Engine.LiveStorage_PlayerDataSetIntByName(0, Engine.SL_GetString("prestige", 0), 0);
				Engine.LiveStorage_PlayerDataSetIntByName(0, Engine.SL_GetString("experience", 0), 0);
			}

			if (ImGui::Button("Set Max Prestige"))
			{
				Engine.LiveStorage_PlayerDataSetIntByName(0, Engine.SL_GetString("prestige", 0), 30);
				Engine.LiveStorage_PlayerDataSetIntByName(0, Engine.SL_GetString("experience", 0), 1002100);
			}

			if (ImGui::Button("Test new commands"))
			{
				
			}
		}
		
		if (ImGui::CollapsingHeader("Host-Menu"))
		{
			UpdateClientVector();
			{
				static int clnt = -1;
				static char buf1[128] = "";

				ImGui::ListBox("", &clnt, [](void* vecc, int idx, const char** out_text)
				{
					std::vector<ClientClass>* vectorr = reinterpret_cast<std::vector<ClientClass>*>(vecc);
					if (idx < 0 || idx >= vectorr->size())
						return false;

					*out_text = vectorr->at(idx).Name.c_str();
					return true;

				}, reinterpret_cast<void*>(&ClientVec), ClientVec.size(), 5);

				int realclient = -1;
				if (clnt != -1)
					realclient = ClientVec[clnt].Index;

				ImGui::Separator();
				if (realclient != -1 && realclient < 18)
				{
					ImGui::Text("Misc Settings");
					ImGui::Checkbox("Explosive Bullets", &Toggles.EB[realclient]);
					//ImGui::Checkbox("UFO", &Toggles.UFO[realclient]);
				//	ImGui::Checkbox("Freeze", &Toggles.freeze[realclient]);

					ImGui::SliderFloat("EB-Radius", &Toggles.EBRADIUS, 0.0f, 1000.0f, "%.2f");
					

					ImGui::Separator();


					//
					ImGui::SameLine();
					ImGui::PushItemWidth(100);



					ImGui::Separator();
					ImGui::Text("Admin Settings");

					ImGui::Separator();
					
					if (ImGui::Button("Give UFO"))
					{
						*(int*)(0x144964810 + (realclient * 0x5758)) = 2;

					}

					if (ImGui::Button("Del UFO"))
					{
						*(int*)(0x144964810 + (realclient * 0x5758)) = 0;

					}
				}
			}
		}

		ImGui::End();
	}
	ImGui::Render();






	   // ImGui::Render();
}