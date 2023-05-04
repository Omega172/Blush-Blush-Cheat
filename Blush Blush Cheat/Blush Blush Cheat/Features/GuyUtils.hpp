#pragma once
#include "Feature.hpp"

// Girls
// Token: 0x0600048A RID: 1162 RVA: 0x00015414 File Offset: 0x00013614
// private void Update()
// Girls.Update()

// Girls
// Token: 0x0600049C RID: 1180 RVA: 0x00016182 File Offset: 0x00014382
// public void UnlockGirl(int girl)
// Girls.UnlockGirl(int girl)

inline void* Guys_ClassInstance = nullptr;

class GuyUtils : public Feature
{
private:
	void* Guys_Update = nullptr;

	void Unlock()
	{
		if (Guys_ClassInstance == nullptr)
			return;
		
		MonoMethod* UnlockGuy = Mono::Instance().GetMethod("Girls", "UnlockGirl", 1);
		if (UnlockGuy == nullptr)
		{
			LogError("UnlockGuy", "Failed to get method pointer");
			return;
		}
		
		for (unsigned int i = 0; i < Guys::MAX + 1; i++)
		{
			void* args[1] = { &i };
			MonoObject* result = Mono::Instance().Invoke(UnlockGuy, Guys_ClassInstance, args);
			
			if (bExtraDebug)
				LogInvoke("Guys.Unlock", "Returned: " + (std::stringstream() << result).str());
		}
	}

	HOOK_DEF(void, Guys_Update, (void* __this))
	{
		Guys_ClassInstance = __this;
		return oGuys_Update(__this);
	}

public:
	GuyUtils() {};
	
	void Render() override
	{
		if (ImGui::Button("Unlock All Guys"))
			Unlock();
	}
	
	void Create() override
	{
		Guys_Update = Mono::Instance().GetCompiledMethod("Girls", "Update", 0);
		if (Guys_Update == nullptr)
		{
			LogHook(HookLogReason::Error, "Guys.Update", "Failed to get method pointer");
		}

		LogHook(HookLogReason::Create, "Guys.Update");
		CreateHook(Guys_Update);

		LogHook(HookLogReason::Enable, "Guys.Update");
		EnableHook(Guys_Update);
	}

	void Destroy() override
	{
		LogHook(HookLogReason::Destroy, "Guys.Update");
		DisableHook(Guys_Update);
	}
};