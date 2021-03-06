// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "d3d11hook.h"

const byte moveax1ret[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 };

HWND curWindow;
WNDPROC oldWindowProc;

bool First = true;

SidazToggles Toggles;
SimEngine Engine;

typedef dvar_t* (__cdecl* tFindDvar)(const char* dvarname);
tFindDvar FindDvar = (tFindDvar)0x1404BF8B0;

enum hitLocation_t
{
	HITLOC_NONE = 0x0,
	HITLOC_HELMET = 0x1,
	HITLOC_HEAD = 0x2,
	HITLOC_NECK = 0x3,
	HITLOC_TORSO_UPR = 0x4,
	HITLOC_TORSO_LWR = 0x5,
	HITLOC_R_ARM_UPR = 0x6,
	HITLOC_L_ARM_UPR = 0x7,
	HITLOC_R_ARM_LWR = 0x8,
	HITLOC_L_ARM_LWR = 0x9,
	HITLOC_R_HAND = 0xA,
	HITLOC_L_HAND = 0xB,
	HITLOC_R_LEG_UPR = 0xC,
	HITLOC_L_LEG_UPR = 0xD,
	HITLOC_R_LEG_LWR = 0xE,
	HITLOC_L_LEG_LWR = 0xF,
	HITLOC_R_FOOT = 0x10,
	HITLOC_L_FOOT = 0x11,
	HITLOC_GUN = 0x12,
	HITLOC_SHIELD = 0x13,
	HITLOC_ARMOR = 0x14,
	HITLOC_SOFT = 0x15,
	HITLOC_NUM = 0x16,
};


void(*Scr_AgentDamage_Stub)(uint64_t self, uint64_t inflictor, uint64_t attacker, int damage, int dflags, int meansOfDeath, int weapon, bool isAlternate, const float *vPoint, const float *vDir, int hitLoc, int timeOffset) = (void(*)(uint64_t, uint64_t, uint64_t, int, int, int, int, bool, const float *, const float *, int, int))0x0000000140331010;

typedef int(__cdecl* tOpenConsole)(void);
tOpenConsole OpenConsole = (tOpenConsole)0x1404D98A0;

typedef void(__cdecl* tVM_Resume)(unsigned int timeId);
tVM_Resume oVM_Resume;

typedef void(__fastcall* tCbuf_AddText)(int localClientNum, const char *text);
tCbuf_AddText Cbuf_AddText = (tCbuf_AddText)0x1403AED70;


typedef __int64(__fastcall* tGScr_AllocString)(const char* string);
tGScr_AllocString GScr_AllocString = (tGScr_AllocString)0x140323610;

typedef void(__fastcall* tvectoangles)(Vector* vec, Vector* retAngles);
tvectoangles vectoangles = (tvectoangles)0x1404B4CF0;

//#define RegisterHook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourAttach(reinterpret_cast<LPVOID*>(&original), reinterpret_cast<LPVOID>(hook)), DetourTransactionCommit())
//#define RemoveHook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourDetach(reinterpret_cast<LPVOID*>(&original), reinterpret_cast<LPVOID>(hook)), DetourTransactionCommit())




void PatchAddy(DWORD_PTR Address, byte * buffer, size_t length)
{
	DWORD one, two;
	VirtualProtect((void*)Address, length, PAGE_EXECUTE_READWRITE, &one);
	memcpy((void*)Address, buffer, length);
	VirtualProtect((void*)Address, length, one, &two);
}


void ReadAddy(DWORD_PTR Address, byte * buffer, size_t length)
{
	DWORD one, two;
	VirtualProtect((void*)Address, length, PAGE_EXECUTE_READWRITE, &one);
	memcpy((void*)buffer, (void*)Address, length);
	VirtualProtect((void*)Address, length, one, &two);
}

void UnlockDLCUnlocks()
{
	PatchAddy(0x1403BD780, (byte*)moveax1ret, ARRAYSIZE(moveax1ret));
}

DWORD WINAPI crashniggers(LPVOID lParam)
{

	byte buf[] = { 0x73, 0x61, 0x79, 0x20, 0x22, 0x5E, 0x02, 0x15, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0x22 };


	Cbuf_AddText(0, "say \"im crashing ur shit bitch\"");
	dvar_t* cg_chattime = FindDvar("cg_chattime");
	cg_chattime->current.integer = 0;

	Sleep(3000);
	Cbuf_AddText(0, ((char*)buf));


	cg_chattime->current.integer = 12000;


	ExitThread(0);
}


LRESULT CALLBACK WndProcc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = CallWindowProc(oldWindowProc, hwnd, uMsg, wParam, lParam);


	//printf("nigggg\n");




	if (uMsg != WM_KEYDOWN)
		return ret;

	if (wParam == VK_F5)
	{
		//if (First)
		{

			dvar_t* data_validation_allow_drop = FindDvar("data_validation_allow_drop");
			data_validation_allow_drop->current.integer = 0;


			dvar_t* party_minplayers = FindDvar("party_minplayers");
			party_minplayers->current.integer = 1;


		//	First = false;
		}
	}
	if (wParam == VK_F6)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)crashniggers, 0, 0, 0);








	}

	//UnlockDLCUnlocks();


	return ret;
}

typedef void(__fastcall* tScr_NotifyNum)(int entnum, unsigned int classnum, int string, unsigned int paramcount);
tScr_NotifyNum oScr_NotifyNum;


const char* (*SL_ConvertToString)(int stringValue) = (const char* (*)(int))0x00000001403F0F10;




struct VariableStackBuffer
{
	const char* pos;
	unsigned __int16 size;
	unsigned __int16 bufLen;
	unsigned __int16 localId;
	char time;
	char buf[1];
};

union VariableUnion
{
	int intValue;
	unsigned int uintValue;
	float floatValue;
	unsigned int stringValue;
	const float* vectorValue;
	const char* codePosValue;
	unsigned int pointerValue;
	VariableStackBuffer* stackValue;
	unsigned int entityOffset;
};

struct VariableValue
{
	VariableUnion u;
	int type;
};

typedef void(__cdecl* tVM_Notify)(unsigned int notifyListOwnerId, int stringValue, VariableValue* top);
tVM_Notify oVM_Notify;


Vector3::Vector3(float _x, float _y, float _z) {
	this->vec[0] = _x;
	this->vec[1] = _y;
	this->vec[2] = _z;
}

Vector3::Vector3(const float * origin) {
	this->vec[0] = origin[0];
	this->vec[1] = origin[1];
	this->vec[2] = origin[2];
}

void Vector3::Add(float val) {
	this->vec[0] += val;
	this->vec[1] += val;
	this->vec[2] += val;
}
void Vector3::Add(Vector3 val) {
	this->vec[0] += val.vec[0];
	this->vec[1] += val.vec[1];
	this->vec[2] += val.vec[2];
}
void Vector3::Add(const float* val) {
	this->vec[0] += val[0];
	this->vec[1] += val[1];
	this->vec[2] += val[2];
}

void Vector3::Subtract(float val) {
	this->vec[0] -= val;
	this->vec[1] -= val;
	this->vec[2] -= val;
}
void Vector3::Subtract(Vector3 val) {
	this->vec[0] -= val.vec[0];
	this->vec[1] -= val.vec[1];
	this->vec[2] -= val.vec[2];
}
void Vector3::Subtract(const float* val) {
	this->vec[0] -= val[0];
	this->vec[1] -= val[1];
	this->vec[2] -= val[2];
}

void Vector3::Divide(float val) {
	this->vec[0] /= val;
	this->vec[1] /= val;
	this->vec[2] /= val;
}
void Vector3::Divide(Vector3 val) {
	this->vec[0] /= val.vec[0];
	this->vec[1] /= val.vec[1];
	this->vec[2] /= val.vec[2];
}
void Vector3::Divide(const float* val) {
	this->vec[0] /= val[0];
	this->vec[1] /= val[1];
	this->vec[2] /= val[2];
}

void Vector3::Multiply(float val) {
	this->vec[0] *= val;
	this->vec[1] *= val;
	this->vec[2] *= val;
}
void Vector3::Multiply(Vector3 val) {
	this->vec[0] *= val.vec[0];
	this->vec[1] *= val.vec[1];
	this->vec[2] *= val.vec[2];
}
void Vector3::Multiply(const float* val) {
	this->vec[0] *= val[0];
	this->vec[1] *= val[1];
	this->vec[2] *= val[2];
}

enum meansOfDeath_t
{
	MOD_UNKNOWN = 0x0,
	MOD_PISTOL_BULLET = 0x1,
	MOD_RIFLE_BULLET = 0x2,
	MOD_EXPLOSIVE_BULLET = 0x3,
	MOD_GRENADE = 0x4,
	MOD_GRENADE_SPLASH = 0x5,
	MOD_PROJECTILE = 0x6,
	MOD_PROJECTILE_SPLASH = 0x7,
	MOD_MELEE = 0x8,
	MOD_HEAD_SHOT = 0x9,
	MOD_MELEE_DOG = 0xA,
	MOD_MELEE_ALIEN = 0xB,
	MOD_CRUSH = 0xC,
	MOD_FALLING = 0xD,
	MOD_SUICIDE = 0xE,
	MOD_TRIGGER_HURT = 0xF,
	MOD_EXPLOSIVE = 0x10,
	MOD_IMPACT = 0x11,
	MOD_NUM = 0x12,
};


typedef void(__fastcall *tG_Damage)(void *targent, void *inflictorent, void *attackerrnt, const Vector *dir, const Vector *point, int damage, int dFlags, int mod, int iweapon, bool isAlternate, int hitLoc, unsigned int modelIndex, void* partName, int timeOffset, int a15);
tG_Damage oG_Damage; //= (tG_Damage)0x1402EB080;


int(*Scr_GetSelf)(unsigned int notifyOwnerId) = (int(*)(unsigned int))0x00000001403F3170;

const float * PlayerCmd_GetAngles(int clientNum) {
	int64_t client = *(int64_t*)(0x0000000144758C70 + (0x2E0 * clientNum) + 0x158);
	float angles[3] = { *(float*)(client + 0x1B4), *(float*)(client + 0x1B8), *(float*)(client + 0x1BC) };
	return angles;
}


void(*AngleVectorss)(const float* angles, float* forward, float* right, float* up) = (void(*)(const float*, float*, float*, float*))0x00000001404B5030;
void(*G_GetPlayerEyePosition)(int64_t ps, float* origin) = (void(*)(int64_t, float*))0x00000001402DC250;
void(*G_LocationalTrace)(trace_t* results, const float* start, const float* end, int passEntityNum, int contentmask) = (void(*)(trace_t *, const float*, const float*, int, int))0x00000001402F7370;
const float* Scr_BulletTrace(int clientNum, const float * start, const float * end) {
	trace_t trace;
	float bullet[3];
	G_LocationalTrace(&trace, start, end, clientNum, 0x280E831);
	bullet[0] = (end[0] - start[0]) * trace.fraction + start[0];
	bullet[1] = (end[1] - start[1]) * trace.fraction + start[1];
	bullet[2] = (end[2] - start[2]) * trace.fraction + start[2];
	return bullet;
}

__int64 Scr_GetEntity(int client) {
	return (0x0000000144758C70 + (client * 0x2E0));
}


const float* scr_Getcoords(int clientNum)
{
	

	uint64_t tempEnt = Scr_GetEntity(clientNum);
	uint64_t tempClient = *(uint64_t*)(tempEnt + 0x158);



	float xyz[3];
	

	xyz[0] = *(float*)(tempClient + 0x78);
	xyz[1] = *(float*)(tempClient + 0x7C);
	xyz[2] = *(float*)(tempClient + 0x80);


	return xyz;
}

typedef void(__fastcall* tG_SetOrigin)(__int64 ent,  Vector3 origin);
tG_SetOrigin G_SetOrigin = (tG_SetOrigin)0x1403D8860;


void* GetEntity(int entnum)
{
	return (void*)(0x0000000144758C70 + (736 * entnum));
}

typedef void(__fastcall* tSetClientOrigin)(void *ent, const float *origin, int teleport);
tSetClientOrigin SetClientOrigin = (tSetClientOrigin)0x1402DC4C0;

bool GenHeadshot()
{
	const int perc = 20;
	return (rand() % 100) <= perc;
}

float GetDistance(Vector3 point1, Vector3 point2) {
	return sqrtf((point1.vec[0] - point2.vec[0]) * (point1.vec[0] - point2.vec[0]) + (point1.vec[1] - point2.vec[1]) * (point1.vec[1] - point2.vec[1]) + (point1.vec[2] - point2.vec[2]) * (point1.vec[2] - point2.vec[2]));
}


typedef signed __int64(__fastcall* tG_DObjGetWorldTagPos)(void *entity, void* stringref, Vector* posRet);
tG_DObjGetWorldTagPos G_DObjGetWorldTagPos = (tG_DObjGetWorldTagPos)0x14033C1A0;




typedef void*(__fastcall* tSV_GetPlayerstateForClientNum)(int num);
tSV_GetPlayerstateForClientNum SV_GetPlayerstateForClientNum = (tSV_GetPlayerstateForClientNum)0x1403D4885;

typedef void(__fastcall* tG_GetPlayerViewOrigin)(void *ps, Vector *origin);
tG_GetPlayerViewOrigin G_GetPlayerViewOrigin = (tG_GetPlayerViewOrigin)0x1402DC340;

struct cmd_function_s {
	cmd_function_s * next;
	const char* name;
	void(*function)();
};

void(*CG_GameMessage)(int local, const char* msg) = (void(*)(int, const char*))0x00000001401A3050;
__int64(*SV_AddTestClient)(bool useBotName) = (__int64(*)(bool))0x0000000140439180;
unsigned int(*Scr_GetSelf2)(__int64 stringValue) = (unsigned int(*)(__int64))0x00000001403F3160;
//const char* (*SL_ConvertToString)(int stringValue) = (const char* (*)(int))0x00000001403F0F00;
void(*Scr_Notify)(__int64 ent, __int64 stringValue, unsigned int paramcount) = (void(*)(__int64, __int64, unsigned int))0x0000000140339120;
__int64(*SL_GetString)(const char* str, unsigned int user) = (__int64(*)(const char*, unsigned int))0x00000001403F1430;
void(*Scr_AddString)(const char* value) = (void(*)(const char*))0x00000001403F7C00;
void(*Scr_AddEntity)(__int64 value) = (void(*)(__int64))0x00000001403388A0;
signed __int64(*SV_SpawnTestClient)(__int64 ent) = (signed __int64(*)(__int64))0x000000014043C740;
__int64(*SV_AddBot)(const char* name) = (__int64(*)(const char*))0x0000000140438EB0;
void(*Cmd_AddCommandInternal)(const char* name, void(*function)(), cmd_function_s* allocedCmd) = (void(*)(const char*, void(*)(), cmd_function_s*))0x00000001403AF2B0;

Vector GetViewOrigin(void* ent)
{
	Vector ret(0, 0, 0);
	void* ps = SV_GetPlayerstateForClientNum(*(int*)ent);
	G_GetPlayerViewOrigin(ps, &ret);
	return ret;
}

void Cmd_MenuResponse_f(__int64 ent, const char* str1, const char* str2) {
	Scr_AddString(str2);
	Scr_AddString(str1);
	Scr_Notify(ent, SL_GetString("menuresponse", 0), 2);
}

__int64 botEnt;
cmd_function_s* cmd_functions;
cmd_function_s AddTestClient_var;
cmd_function_s AddToTeam_var;
cmd_function_s AddClass_var;


char MasterBuffer[0x1000];

char* va(const char* Text, ...)
{
	va_list parameters;
	va_start(parameters, Text);
	vsprintf_s(MasterBuffer, Text, parameters);
	return MasterBuffer;
}


void AddTestClient_f() {
	botEnt = SV_AddBot(va("^%iSidazBot", rand() % 9));
	Scr_AddEntity(botEnt);
	SV_SpawnTestClient(botEnt);
}

void AddToTeam_f() {
	Cmd_MenuResponse_f(botEnt, "team_marinesopfor", "autoassign");
}

void AddClass_f() {
	Cmd_MenuResponse_f(botEnt, "changeclass", "class1");
}


bool firsttime = true;
bool depatch = true;
//extern void(*G_RadiusDamage)(const float* origin, uint64_t inflictor, uint64_t attacker, float fInnerDamage, float fOuterDamage, float radius, float coneAngleCos, float* coneDirection, uint64_t ignore, meansOfDeath_t mod, int weapon, bool isAlternate);
//gentity_s *self, gentity_s *inflictor, gentity_s *attacker, int damage, int meansOfDeath, int iWeapon, const float *vDir, hitLocation_t hitLoc, int psTimeOffset
void(*player_die)(uint64_t self, uint64_t inflictor, uint64_t attacker, int damage, int meansOfDeath, int iWeapon, const float *vDir, hitLocation_t hitLoc, int psTimeOffset) = (void(*)(uint64_t, uint64_t, uint64_t, int, int, int, const float*, hitLocation_t, int))0x00000001402ED330;
void(*G_RadiusDamage)(const float* origin, uint64_t inflictor, uint64_t attacker, float fInnerDamage, float fOuterDamage, float radius, float coneAngleCos, float* coneDirection, uint64_t ignore, meansOfDeath_t mod, int weapon, bool isAlternate) = (void(*)(const float*, uint64_t, uint64_t, float, float, float, float, float*, uint64_t, meansOfDeath_t, int, bool))0x00000001402EC6D0;
void(*G_Damage)(uint64_t targent, uint64_t inflictorent, uint64_t attackerrnt, const Vector *dir, const Vector *point, int damage, int dFlags, int mod, int iweapon, bool isAlternate, int hitLoc, unsigned int modelIndex, void* partName, int timeOffset, int a15) = (void(*)(uint64_t, uint64_t, uint64_t , const Vector *, const Vector *, int , int , int , int , bool , int , unsigned int , void* , int , int ))0x00000001402EB080;

void VM_Notify(unsigned int notifyListOwnerId, int stringValue, VariableValue* top)
{
//	printf("notify: %s\n", SL_ConvertToString(stringValue));

	const char * nigga = SL_ConvertToString(stringValue);

	/*if (firsttime)
	{

		Cmd_AddCommandInternal("addclass", AddClass_f, &AddClass_var);
		Cmd_AddCommandInternal("addteam", AddToTeam_f, &AddToTeam_var);
		Cmd_AddCommandInternal("addtestclient", AddTestClient_f, &AddTestClient_var);

		firsttime = false;
	}*/


	

	oVM_Notify(notifyListOwnerId, stringValue, top);
}


void __fastcall hk_G_Damage(void *targent, void *inflictorent, void *attackerrnt, const Vector *dir, const Vector *point, int damage, int dFlags, int mod, int iweapon, bool isAlternate, hitLocation_t hitLoc, unsigned int modelIndex, void* partName, int timeOffset, int a15)
{

	//printf("mod: %i hitloc: %i damage: %i modelindex: %i partname: %i", mod, hitLoc, damage, modelIndex, partName);
	//printf("targent: %p, inflictorent: %p, attackerrnt: %p, dir: %f, point: %f, damage: %i, dflagd: %i, mod: %i , iweapon: %i, isalternate: %i, hitloc %i, modelindex: %i, partname: %i, timeoffset: %i, a15: %i\n", targent, inflictorent, attackerrnt, dir, point, damage, dFlags, mod, iweapon, isAlternate, hitLoc, modelIndex, partName, timeOffset, a15);


	//printf("iweapon: %i, %s, %x\n", iweapon);
	

	oG_Damage(targent, inflictorent, attackerrnt, dir, point, damage, dFlags, mod, iweapon, isAlternate, hitLoc, modelIndex, partName, timeOffset, a15);
}


const float* GetCoords(uint64_t clientNum) {

	float coords[3];

	

	//bullet[0] = (end[0] - start[0]) * trace.fraction + start[0];
	//bullet[1] = (end[1] - start[1]) * trace.fraction + start[1];
	//bullet[2] = (end[2] - start[2]) * trace.fraction + start[2];
	coords[0] = *(float*)(clientNum + 0x78);
	coords[1] = *(float*)(clientNum + 0x7C);
	coords[2] = *(float*)(clientNum + 0x80);

	return coords;

}

void(*player_die_stub)(uint64_t selfent, uint64_t inflictorent, uint64_t attackerent, int damage, int meansOfDeath, void* iWeapon, bool isAlternate, const float *vDir, hitLocation_t hitLoc, int psTimeOffset) = (void(*)(uint64_t, uint64_t, uint64_t, int, int, void*, bool, const float *, hitLocation_t, int))0x00000001402ED330;
void(*G_DamageNotify_Stub)(unsigned int notify, uint64_t targ, uint64_t attacker, const float *dir, const float *point, int damage, int mod, int dFlags, unsigned int modelIndex, unsigned int partName, int weapon, bool isAlternate) = (void(*)(unsigned int , uint64_t , uint64_t , const float *, const float *, int , int , int , unsigned int , unsigned int , int , bool ))0x00000001402EB8D0;

const LPCSTR AppWindowTitle = "Call of Duty®: Advanced Warfare Multiplayer"; // Targeted D11 Application Window Title.
HWND hWnd = GetForegroundWindow();

void(*VM_Notify_Stub)(unsigned int notifyListOwnerId, int stringValue, VariableValue* top) = (void(*)(unsigned int, int, VariableValue*))0x00000001403FD5B0;



void eb(int clientt)
{

	{



		//printf("notify: %s\n", SL_ConvertToString(stringValue));

		uint64_t client = *(int64_t*)(0x0000000144758C70 + (0x2E0 * clientt) + 0x158);


		//uint64_t clientlocal = *(int64_t*)(0x000000014427A0E0 + (0x2F0 * *Engine.LocalPlayer) + 0x168);
		//void* ent = Engine.GetEntity(realclient);
		//void* localEnt = Engine.GetEntity(*Engine.LocalPlayer);

		Vector3 forwardedAngles = Vector3(0, 0, 0);
		Vector3 angles = Vector3(PlayerCmd_GetAngles(clientt)[0], PlayerCmd_GetAngles(clientt)[1], PlayerCmd_GetAngles(clientt)[2]);
		Vector3 getEye = Vector3(0, 0, 0);

		//Engine.Add_Ammo(client, *(int*)(client + 0x41C), 0, 999, 1);

		AngleVectorss(angles.vec, forwardedAngles.vec, NULL, NULL);
		G_GetPlayerEyePosition(client, getEye.vec);
		forwardedAngles.Multiply(999999);


		Vector3 end = Vector3(Scr_BulletTrace(client, getEye.vec, forwardedAngles.vec));


		//G_RadiusDamage(end.vec, Scr_GetEntity(clientt), Scr_GetEntity(clientt), 999, 999, Toggles.EBRADIUS, 0, NULL, Scr_GetEntity(clientt), MOD_RIFLE_BULLET, *(int*)(client + 0x41C), false);

		G_RadiusDamage(end.vec, Scr_GetEntity(clientt), Scr_GetEntity(clientt), 999, 999, Toggles.EBRADIUS, 0, NULL, Scr_GetEntity(clientt), MOD_RIFLE_BULLET, *(int*)(client + 0x41C), false);


		
	}
}


void hk_Scr_NotifyNum(int entnum, unsigned int classnum, int string, unsigned int paramcount)
{

	//return;
	oScr_NotifyNum(entnum, classnum, string, paramcount);

	

	//printf("notify: %s\n", SL_ConvertToString(string));
	if (Toggles.EB[entnum])
	{

		const char* nigga = SL_ConvertToString(string);

		if (!strcmp(nigga, "weapon_fired"))
		{
			printf("shot!\n");
			eb(entnum);





		}

	}

	//GScr_AllocString


}

DWORD WINAPI MainThread(HMODULE lpvoid)
{
	//Sleep(10000);


	ImplHookDX11_Init(lpvoid, FindWindow(0, AppWindowTitle));

	

	//MH_CreateHook((void*)0x1403FDA80, (void*)hk_VM_Resume, (LPVOID*)&oVM_Resume);
	//MH_EnableHook((void*)0x1403FDA80);
	//MH_CreateHook((void*)0x1402EB080, (void*)hk_G_Damage, (LPVOID*)&oG_Damage);
	//MH_EnableHook((void*)0x1402EB080);


	//UnlockDLCUnlocks();

	



	ExitThread(0);
}



bool(*BG_BotSystemEnabled_Stub)() = (bool(*)())0x0000000140560780;





bool BG_BotSystemEnabled_Hook()
{
	printf("bots\n");
	return false;
}



//MH_CreateHook((void*)0x1403FDA80, (void*)hk_VM_Resume, (LPVOID*)&oVM_Resume);
	//MH_EnableHook((void*)0x1403FDA80);



void VM_Notify_Hook(unsigned int notifyListOwnerId, int stringValue, VariableValue* top) {
	int clientNum = Scr_GetSelf(notifyListOwnerId);
	//const char* notify = SL_ConvertToString(stringValue);

	if (Toggles.EB[clientNum])
	{

		const char* nigga = SL_ConvertToString(stringValue);

		if (!strcmp(nigga, "end_firing"))
		{
			printf("shot!\n");
			eb(clientNum);





		}

	}
	VM_Notify_Stub(notifyListOwnerId, stringValue, top);
}




void Scr_AgentDamage_Hook(uint64_t self, uint64_t inflictor, uint64_t attacker, int damage, int dflags, int meansOfDeath, int weapon, bool isAlternate, const float *vPoint, const float *vDir, hitLocation_t hitLoc, int timeOffset)
{
	printf("self: %p, inflictor: %p, attacker: %p, damage: %i, dflags: %i, meansOfDeath: %i, weapon: %i, mod: %i , weapon: %i, isalternate: %i, vPoint %d, vDir: %d, hitLoc: %i, timeoffset: %i\n", self, inflictor, attacker, damage, dflags, meansOfDeath, weapon, isAlternate, vPoint, isAlternate, hitLoc, vDir, hitLoc, timeOffset);

	Scr_AgentDamage_Stub(self, inflictor, attacker, damage, dflags, meansOfDeath, weapon, isAlternate, vPoint, vDir, hitLoc, timeOffset);
}

typedef void(__fastcall* tplayer_die)(void* selfent, void* inflictorent, void* attackerent, int damage, int meansOfDeath, void* iWeapon, bool isAlternate, const float *vDir, hitLocation_t hitLoc, int psTimeOffset);
tplayer_die oplayer_die;


void player_die_hook(uint64_t selfent, uint64_t inflictorent, uint64_t attackerent, int damage, int meansOfDeath, void* iWeapon, bool isAlternate, const float *vDir, hitLocation_t hitLoc, int psTimeOffset)
{
	//printf("self: %p, inflictor: %p, attacker: %p, damage: %i, dflags: %i, meansOfDeath: %i, weapon: %i, mod: %i , weapon: %i, isalternate: %i, vPoint %d, vDir: %d, hitLoc: %i, timeoffset: %i\n", self, inflictor, attacker, damage, dflags, meansOfDeath, weapon, isAlternate, vPoint, isAlternate, hitLoc, vDir, hitLoc, timeOffset);

	player_die_stub( selfent,  inflictorent,  attackerent,  damage,  meansOfDeath,  iWeapon,  isAlternate, vDir,  hitLoc,  psTimeOffset);
}

DWORD WINAPI Main(LPVOID lParam)
{
	Sleep(1000);
	RegisterHook(VM_Notify_Stub, VM_Notify_Hook);
	RegisterHook(Scr_AgentDamage_Stub, Scr_AgentDamage_Hook);
	RegisterHook(player_die_stub, player_die_hook);
	RegisterHook(BG_BotSystemEnabled_Stub,BG_BotSystemEnabled_Hook);

	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	printf("nigggg\n");

	//UnlockDLCUnlocks();

	ExitThread(0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);

	    break;
	case DLL_THREAD_ATTACH:

		

	case DLL_THREAD_DETACH:
		
		break;
	}
	return TRUE;
}
