#pragma once
#define WIN32_LEAN_AND_MEAN

#define VERSION "1.0.2"

#include <Windows.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <D3D11.h>
#include <DXGI.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/object.h>

inline bool bExit = false;
inline bool bExtraDebug = false;

// Main
#include "Main/Main.hpp"

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "GUI/Custom.hpp"

// Utils
#include "Utils/Console/Console.hpp"
#include "Utils/Logging/Color.hpp"
#include "Utils/Logging/Logging.hpp"
#include "Utils/MiscUtils.hpp"

// Hooking
#include "Hooking/Keiro/kiero.h"
#include "Hooking/Keiro/minhook/include/MinHook.h"
#include "Hooking/Hook.h"

// SDK
inline std::string monoDll = "mono-2.0-bdwgc.dll";
#include "SDK/Mono.hpp"
#include "SDK/Enums.hpp"

// Features
#include "Features/Watermark.hpp"
inline bool bWatermark = true;
inline bool bWatermarkFPS = true;
#include "Features/GameState.hpp"
inline GameState gameState;
#include "Features/PhoneUtils.hpp"
inline PhoneUtils phoneUtils;
#include "Features/GiveDiamonds.hpp"
inline GiveDiamonds giveDiamonds;
#include "Features/GuyUtils.hpp"
inline GuyUtils guyUtils;
#include "Features/MiscUnlockers.hpp"
inline MiscUnlockers miscUnlockers;
#include "Features/Jobs.hpp"
inline Jobs jobs;
#include "Features/SpeedHack.hpp"
inline SpeedHack speedHack;
#include "Features/UnlockItems.hpp"
inline UnlockItems unlockItems;

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;
