#pragma once
#include "Feature.hpp"

// GameState
// Token: 0x040001EF RID: 495
// public static bool Initialized = false;
// GameState.Initalized

// GameState
// Token: 0x060003EF RID: 1007 RVA: 0x0001067E File Offset: 0x0000E87E
// public void Quit()
// GameState.Quit()

// GameState
// Token: 0x040001D4 RID: 468
// public static bool NSFW = false;
// GameState.NSFW

// GameState
// Token: 0x06000395 RID: 917 RVA: 0x0000D438 File Offset: 0x0000B638
// public static bool SpeedDatingEnabled()
// GameState.SpeedDatingEnabled()

inline bool speedToggle = true;

class GameState : public Feature
{
private:
	void* GameState_Quit = nullptr;
	bool* GameState_NFSW = nullptr;
	void* GameState_SpeedDatingEnabled = nullptr;

	bool nsfwRestore = false;
	bool nsfwToggle = false;

	void Initalize()
	{
		bool* isInitialized = (bool*)Mono::Instance().GetStaticFieldValue("GameState", "Initialized");
		if (isInitialized == nullptr)
		{
			LogError("GameState", "Unable to retieve a pointer to GameState.Initialized");
			bExit = true;
			return;
		}

		(*isInitialized) ? Log("GameState", "GameState::Initialized = True | Continuing with initialization") : Log("GameState_Initialized", "GameState::Initialized = False | Waiting for game to initialize");
		while (!*isInitialized)
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

		return;
	}

	void Toggle()
	{
		if (GameState_NFSW == nullptr)
			return;

		if (nsfwToggle && !*GameState_NFSW)
		{
			*GameState_NFSW = true;
			Log("GameState", "GameState.NSFW = True");
		}
		else if (!nsfwToggle && *GameState_NFSW)
		{
			*GameState_NFSW = false;
			Log("GameState", "GameState.NSFW = False");
		}
	}

	HOOK_DEF(void, GameState_Quit, (void* __this))
	{
		bExit = true;
		return oGameState_Quit(__this);
	}

	HOOK_DEF(bool, GameState_SpeedDatingEnabled, (void* __this))
	{
		if (bExtraDebug)
			Log("GameState.SpeedDatingEnabled", "Called");

		if (speedToggle)
			return true;

		return oGameState_SpeedDatingEnabled(__this);
	}

public:
	GameState() {}

	void Render() override
	{
		ImGui::Checkbox("NSFW Features", &nsfwToggle);
		ImGui::Checkbox("Enable Speed Feature", &speedToggle);

		Toggle();
	}

	void Create() override
	{
		Initalize();

		GameState_Quit = Mono::Instance().GetCompiledMethod("GameState", "Quit", 0);
		if (GameState_Quit == nullptr)
			LogHook(HookLogReason::Error, "GameState.Quit", "Unable to retieve a pointer to GameState.Quit");
		else
		{
			LogHook(HookLogReason::Create, "GameState.Quit", "GameState.Quit Hook Created");
			CreateHook(GameState_Quit);

			LogHook(HookLogReason::Enable, "GameState.Quit", "GameState.Quit Hook Enabled");
			EnableHook(GameState_Quit);
		}

		GameState_NFSW = (bool*)Mono::Instance().GetStaticFieldValue("GameState", "NSFW");
		if (GameState_NFSW == nullptr)
			LogError("GameState.NSFW", "Unable to retieve a pointer to GameState.NSFW");
		else
		{
			std::string state = (*GameState_NFSW) ? "True" : "False";
			Log("GameState.NSFW", "GameState.NSFW = " + state);
			nsfwRestore = *GameState_NFSW;
			nsfwToggle = *GameState_NFSW;
		}

		GameState_SpeedDatingEnabled = Mono::Instance().GetCompiledMethod("GameState", "SpeedDatingEnabled", 0);
		if (GameState_SpeedDatingEnabled == nullptr)
		{
			LogError("GameState.SpeedDatingEnabled", "Failed to get method pointer");
		}
		else
		{
			LogHook(HookLogReason::Create, "GameState.SpeedDatingEnabled");
			CreateHook(GameState_SpeedDatingEnabled);

			LogHook(HookLogReason::Enable, "GameState.SpeedDatingEnabled");
			EnableHook(GameState_SpeedDatingEnabled);
		}
	}

	void Destroy() override
	{
		LogHook(HookLogReason::Destroy, "GameState.Quit", "GameState.Quit Hook Destroyed");
		DisableHook(GameState_Quit);

		nsfwToggle = nsfwRestore;

		if (GameState_NFSW)
			*GameState_NFSW = nsfwRestore;

		std::string state = (nsfwRestore) ? "True" : "False";
		Log("GameState.NSFW", "GameState.NSFW restored to " + state);

		LogHook(HookLogReason::Destroy, "GameState.SpeedDatingEnabled");
		DisableHook(GameState_SpeedDatingEnabled);
	}
};