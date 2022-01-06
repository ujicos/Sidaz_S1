#include "stdafx.h"

#include "imgui\imgui.h"


/*typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall *D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall *D3D11ClearRenderTargetViewHook) (ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

typedef LRESULT(__fastcall* tWndProcc)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
tWndProcc oWndProc;

HWND curWindow;
WNDPROC oldWindowProc;

ID3D11Device *pDevice = NULL;
ID3D11DeviceContext *pContext = NULL;

bool done = false;

DWORD_PTR* pSwapChainVtable = NULL;
DWORD_PTR* pDeviceContextVTable = NULL;

D3D11PresentHook phookD3D11Present = NULL;
D3D11DrawIndexedHook phookD3D11DrawIndexed = NULL;
D3D11ClearRenderTargetViewHook phookD3D11ClearRenderTargetView = NULL;
ID3D11RenderTargetView*  g_pRenderTargetView = NULL;

typedef LRESULT ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND hWnd;
bool firstTime = true;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI hk_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // i can basically use the menu once but after it doesnt work anymore
{

	
	switch (msg)
	{
	case WM_SIZE:
		if (pDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX11_InvalidateDeviceObjects();
		}
		break;
	case WM_KEYDOWN:
		Toggles.HandleKeys(wParam);
		break;
	}

	if (!firstTime)
	{

		ImGui::GetIO().MouseDrawCursor = Toggles.HostMenu || Toggles.ModMenu|| Toggles.menuaw;
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		if (Toggles.HostMenu || Toggles.ModMenu || Toggles.menuaw)
			return true;
	}

	return oWndProc(hWnd, msg, wParam, lParam);
}


LRESULT CALLBACK WndProcc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = CallWindowProc(oldWindowProc, hwnd, uMsg, wParam, lParam);



	

	switch (uMsg)
	{
	case WM_SIZE:
		if (pDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX11_InvalidateDeviceObjects();
		}
		break;
	case WM_KEYDOWN:
		Toggles.HandleKeys(wParam);
		break;
	}

	if (!firstTime)
	{
		ImGui::GetIO().MouseDrawCursor = Toggles.HostMenu || Toggles.ModMenu || Toggles.menuaw;
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		if (Toggles.HostMenu || Toggles.ModMenu || Toggles.menuaw)
			return true;
	}

//	return oWndProc(hWnd, msg, wParam, lParam);






	return ret;
}




HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{

	//printf("getting done nigga!\n");
	if (firstTime)
	{
		pSwapChain->GetDevice(__uuidof(pDevice), (void**)&pDevice);
		pDevice->GetImmediateContext(&pContext);

		//ID3D11Texture2D* renderTargetTexture = nullptr;

		//if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture))))
		//{
		//	pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &g_pRenderTargetView);
		//	renderTargetTexture->Release();
		//}
		//InitializeDvars();

		ImGui::CreateContext();
		ImGui_ImplDX11_Init(hWnd, pDevice, pContext);
		GameMenu::SetupMenu();
		ImGui_ImplDX11_CreateDeviceObjects();

		firstTime = false;
	}

	if (Toggles.HostMenu || Toggles.ModMenu || Toggles.menuaw)
	{
		//pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);


		ImGui_ImplDX11_NewFrame();
		GameMenu::DrawMenu();
		ImGui::Render();


		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	//pContext->Flush();

	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

void __stdcall hookD3D11DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	return phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

void __stdcall hookD3D11ClearRenderTargetView(ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4])
{
	phookD3D11ClearRenderTargetView(pContext, pRenderTargetView, ColorRGBA);
	ImGui_ImplDX11_CreateDeviceObjects();
}

void* DetourFunc64(byte* origFunc, byte* hooKFunc)
{
	void* ret = 0;
	MH_CreateHook((void*)origFunc, (void*)hooKFunc, (LPVOID*)&ret);
	MH_EnableHook((void*)origFunc);
	return ret;
}

void RemoveDetour64(byte* origFunc)
{
	MH_RemoveHook(origFunc);
}




void InitializeHook()
{
	hWnd = *(HWND*)0x14B5B9D70;
	IDXGISwapChain* pSwapChain;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = GetWindowLongA(hWnd, GWL_STYLE) & WS_POPUP != 0 ? FALSE : TRUE;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, NULL, &pContext)))
	{
		printf("Failed to create directX device and swapchain stupid nigga!\n");
		return;
	}

	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pDeviceContextVTable = (DWORD_PTR*)pContext;
	pDeviceContextVTable = (DWORD_PTR*)pDeviceContextVTable[0];

	phookD3D11Present = (D3D11PresentHook)DetourFunc64((BYTE*)pSwapChainVtable[8], (BYTE*)hookD3D11Present);
	phookD3D11DrawIndexed = (D3D11DrawIndexedHook)DetourFunc64((BYTE*)pDeviceContextVTable[12], (BYTE*)hookD3D11DrawIndexed);
	phookD3D11ClearRenderTargetView = (D3D11ClearRenderTargetViewHook)DetourFunc64((BYTE*)pDeviceContextVTable[50], (BYTE*)hookD3D11ClearRenderTargetView);

	
	curWindow = FindWindow(NULL, "Call of Duty®: Advanced Warfare Multiplayer");
	oldWindowProc = (WNDPROC)SetWindowLongPtr(curWindow, GWLP_WNDPROC, (LONG_PTR)WndProcc);

	//oWndProc = (tWndProcc)DetourFunc64((BYTE*)0x1404DB180, (BYTE*)hk_WndProc);

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();

	//return;
	done = true;
}


void D3DHook::Hook()
{
	if (!done)
		InitializeHook();
	//InitializeHook();
}*/