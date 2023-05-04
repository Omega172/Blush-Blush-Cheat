#pragma once
#include "Feature.hpp"

// Cellphone
// Token: 0x0600065C RID: 1628 RVA: 0x00026D68 File Offset: 0x00024F68
// private void Update()
// Cellphone.Update()

// Cellphone
// Token: 0x0600065E RID: 1630 RVA: 0x000272D8 File Offset: 0x000254D8
// public void Debug_SkipMessage()
// Cellphone.Debug_SkipMessage()

// Cellphone
// Token: 0x06000638 RID: 1592 RVA: 0x000251FC File Offset: 0x000233FC
// public static bool IsUnlocked(short id)
// Cellphone.IsUnlocked(short)

inline void* Phone_ClassInstance = nullptr;
inline bool unlockContactsToggle = false;

class PhoneUtils : public Feature
{
private:
	void* Phone_Update = nullptr;
	void* Phone_IsUnlocked = nullptr;

	bool skipToggle = false;

	void Skip()
	{
		if (Phone_ClassInstance == nullptr)
			return;

		MonoMethod* Debug_SkipMessage = Mono::Instance().GetMethod("Cellphone", "Debug_SkipMessage", 0);
		if (Debug_SkipMessage == nullptr)
		{
			LogError("Debug_SkipMessage", "Failed to get method pointer");
			return;
		}
		
		MonoObject* result = Mono::Instance().Invoke(Debug_SkipMessage, Phone_ClassInstance, nullptr);
		if (bExtraDebug)
			LogInvoke("Phone.Skip", "Debug_SkipMessage returned: " + (std::stringstream() << result).str());
	};

	HOOK_DEF(void, Phone_Update, (void* __this))
	{
		Phone_ClassInstance = __this;
		return oPhone_Update(__this);
	}

	HOOK_DEF(bool, Phone_IsUnlocked, (void* __this, short id))
	{
		if (unlockContactsToggle)
			return true;

		return oPhone_IsUnlocked(__this, id);
	}
	
public:
	PhoneUtils() {};

	void Render() override
	{
		if (ImGui::Button("Skip Phone Timer"))
			Skip();
		
		ImGui::SameLine();

		ImGui::Checkbox("Toggle", &skipToggle);
		
		ImGui::Checkbox("Unlock all Phone contacts", &unlockContactsToggle);

		if (skipToggle)
			Skip();
	}

	void Create() override
	{
		Phone_Update = Mono::Instance().GetCompiledMethod("Cellphone", "Update", 0);
		if (Phone_Update == nullptr)
		{
			LogHook(HookLogReason::Error, "Phone_Update", "Failed to get method pointer");
		}
		else
		{
			LogHook(HookLogReason::Create, "Phone_Update");
			CreateHook(Phone_Update);

			LogHook(HookLogReason::Enable, "Phone_Update");
			EnableHook(Phone_Update);
		}

		Phone_IsUnlocked = Mono::Instance().GetCompiledMethod("Cellphone", "IsUnlocked", 1);
		if (Phone_IsUnlocked == nullptr)
		{
			LogHook(HookLogReason::Error, "Phone_IsUnlocked", "Failed to get method pointer");
		}
		else
		{
			LogHook(HookLogReason::Create, "Phone_IsUnlocked");
			CreateHook(Phone_IsUnlocked);

			LogHook(HookLogReason::Enable, "Phone_IsUnlocked");
			EnableHook(Phone_IsUnlocked);
		}
	}

	void Destroy() override
	{
		LogHook(HookLogReason::Destroy, "Phone_Update");
		DisableHook(Phone_Update);

		LogHook(HookLogReason::Destroy, "Phone_IsUnlocked");
		DisableHook(Phone_IsUnlocked);
	}
};