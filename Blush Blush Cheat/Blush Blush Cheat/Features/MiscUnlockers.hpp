#pragma once
#include "Feature.hpp"

// Settings
// Token: 0x06000729 RID: 1833 RVA: 0x0002CEE2 File Offset: 0x0002B0E2
// public static bool get_FullVoicesEnabled()
// Settings.get_FullVoicesEnabled()

class MiscUnlockers : Feature
{
private:
	void* Settings_FullVoicesEnabled = nullptr;

	HOOK_DEF(int, Settings_FullVoicesEnabled, (void* __this))
	{
		if (bExtraDebug)
			Log("Settings.FullVoicesEnabled", "Called");
		
		return true;
	}

public:
	MiscUnlockers() {};

	void Render() override 
	{
		
	}
	
	void Create() override 
	{
		Settings_FullVoicesEnabled = Mono::Instance().GetCompiledMethod("Settings", "get_FullVoicesEnabled", 0);
		if (Settings_FullVoicesEnabled == nullptr)
		{
			LogError("Settings.FullVoicesEnabled", "Failed to get method pointer");
		}
		else
		{
			LogHook(HookLogReason::Create, "Settings.FullVoicesEnabled");
			CreateHook(Settings_FullVoicesEnabled);

			LogHook(HookLogReason::Enable, "Settings.FullVoicesEnabled");
			EnableHook(Settings_FullVoicesEnabled);
		}
	}

	void Destroy() override 
	{
		LogHook(HookLogReason::Destroy, "Settings.FullVoicesEnabled");
		DisableHook(Settings_FullVoicesEnabled);
	}
};