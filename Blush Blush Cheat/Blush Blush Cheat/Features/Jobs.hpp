#pragma once
#include"Feature.hpp"

// Job2
// Token: 0x06000512 RID: 1298 RVA: 0x0001B364 File Offset: 0x00019564
// private void Update()
// Job2.Update()

// Job2
// Token: 0x06000510 RID: 1296 RVA: 0x0001B0DC File Offset: 0x000192DC
// private void Unlock()
// Job2.Unlock()

inline bool jobUnlockToggle = false;

class Jobs : Feature
{
private:
	void* Job_Update = nullptr;

	HOOK_DEF(void, Job_Update, (void* __this))
	{
		
		if (jobUnlockToggle)
		{
			MonoMethod* Job_Unlock = Mono::Instance().GetMethod("Job2", "Unlock", 0);
			if (Job_Unlock == nullptr)
			{
				LogError("Job2.Unlock", "Failed to get method pointer");
				return oJob_Update(__this);
			}

			MonoObject* result = Mono::Instance().Invoke(Job_Unlock, __this, nullptr);
			if (bExtraDebug)
				LogInvoke("Job_Unlock", "Result = " + (std::stringstream() << result).str());
		}

		return oJob_Update(__this);
	}

public:
	Jobs() {}

	void Render() override
	{
		ImGui::Checkbox("Unlock All Jobs", &jobUnlockToggle);
	}

	void Create() override
	{
		Job_Update = Mono::Instance().GetCompiledMethod("Job2", "Update", 0);
		if (Job_Update == nullptr)
		{
			LogError("Job2.Update", "Failed to get method pointer");
		}
		else
		{
			LogHook(HookLogReason::Create, "Job2.Update");
			CreateHook(Job_Update);

			LogHook(HookLogReason::Enable, "Job2.Update");
			EnableHook(Job_Update);
		}
	}
	
	void Destroy() override
	{
		LogHook(HookLogReason::Destroy, "Job2.Update");
		DisableHook(Job_Update);
	}
};