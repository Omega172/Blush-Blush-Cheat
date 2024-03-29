#include "Main.hpp"
#include "../GUI/GUI.hpp"
#include "../GUI/Style.hpp"

bool keiroInit = false;
bool hkInit = false;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

int screenX = GetSystemMetrics(SM_CXSCREEN);
int screenY = GetSystemMetrics(SM_CYSCREEN);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void InitImGui();
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

void Init()
{
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			keiroInit = true;
		}
	} while (!keiroInit);

	MH_Initialize();

	// Init Hooks
	gameState.Create();
	phoneUtils.Create();
	giveDiamonds.Create();
	guyUtils.Create();
	miscUnlockers.Create();
	jobs.Create();
	unlockItems.Create();
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	Init();
	
	do
	{
		if (GetAsyncKeyState(VK_INSERT) & 0x1)
			GUI::bMenuOpen = !GUI::bMenuOpen;
		
		if (GetAsyncKeyState(VK_END) & 0x1)
			bExit = true;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	} while (!bExit);

	// Restore Hooks & Disable features
	gameState.Destroy();
	phoneUtils.Destroy();
	giveDiamonds.Destroy();
	guyUtils.Destroy();
	miscUnlockers.Destroy();
	jobs.Destroy();
	unlockItems.Destroy();
	
	MH_Uninitialize();

	std::this_thread::sleep_for(std::chrono::seconds(3));
	con.Free();
	FreeLibraryAndExitThread((HMODULE)lpReserved, EXIT_SUCCESS);
	return 0;
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*
	if (GUI::bMenuOpen)
	{		
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}
	*/
	
	if (GUI::bMenuOpen && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!hkInit)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			if (pBackBuffer != NULL)
				pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			hkInit = true;
			return oPresent(pSwapChain, SyncInterval, Flags);
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	
	GUI::BeginRender();
	ImGui::PushFont(tahomaFont);
	GUI::Render();
	ImGui::PopFont();
	GUI::EndRender();
	
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (bExit)
	{
		pDevice->Release();
		pContext->Release();
		pSwapChain->Release();
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc));
		oPresent(pSwapChain, SyncInterval, Flags);
		kiero::shutdown();
		return 0;
	}

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);

	SetupStyle();
	ImportFonts();
}
