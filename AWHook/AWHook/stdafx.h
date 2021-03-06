// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN 
#define _CRT_SECURE_NO_WARNINGS // Exclude rarely-used stuff from Windows headers
// Windows Header Files:


#include <cmath>


#include <iostream>
#include "windows.h"
#include "MinHook.h"
//#include "dlcunlock.h"
#include "S1.h"
#include "DLCUnlock.h"
#include "Engine.h"
#include <Vector>
#include <windows.h>
#include <iostream>

#include <cmath>
#include <string>
#include <ctime>
#include "MinHook.h"
#include <D3D11.h>
#include <D3DCompiler.h>
#include "vector.h"
#include "Utils.h"
#include "ToggleManager.h"
#include "D3DManager.h"

#include "../AWHook/Detours/detours64.h"



#include "../AWHook/Imgui/imgui.h"
#include "../AWHook/Imgui/imgui_impl_dx11.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"detours64.lib")

#define RegisterHook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourAttach(reinterpret_cast<LPVOID*>(&original), reinterpret_cast<LPVOID>(hook)), DetourTransactionCommit())
#define RemoveHook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourDetach(reinterpret_cast<LPVOID*>(&original), reinterpret_cast<LPVOID>(hook)), DetourTransactionCommit())



// TODO: reference additional headers your program requires here
