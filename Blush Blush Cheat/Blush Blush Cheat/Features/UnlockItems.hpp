#pragma once
#include "Feature.hpp"

// Store2
// Token: 0x0600078E RID: 1934 RVA: 0x000303F0 File Offset: 0x0002E5F0
// private void Update()
// Store2.Update()

// Store2
// Token: 0x060007B5 RID: 1973 RVA: 0x00034154 File Offset: 0x00032354
// private void AwardBlayfapItem(Store2::PurchaseType purchaseType, bool showPopupOnFail, int diamondCost, void* onSucess, void* onFail)
// Store2.AwardBlayfapItem(Store2::PurchaseType purchaseType, bool showPopupOnFail, int diamondCost, void* onSucess, void* onFail)

inline void* Store2_ClassInstance = nullptr;

class UnlockItems : Feature
{
private:
	void* Store2_Update = nullptr;

	void Run()
	{
		if (Store2_ClassInstance == nullptr)
			return;

		for (int i = 0; i < Store2::PurchaseType::MAX; i++)
		{
			AddItem(i, true, 0);
		}
	}

	void AddItem(int purchaseType, bool showPopupOnFail, int diamondCost)
	{
		MonoMethod* AwardBlayfapItem = Mono::Instance().GetMethod("Store2", "AwardBlayfapItem", 5);
		if (AwardBlayfapItem == nullptr)
		{
			LogError("UnlockItems", "Unable to retieve a pointer to Store2.AwardBlayfapItem");
			return;
		}

		void* args[5] = { &purchaseType, &showPopupOnFail, &diamondCost, NULL, NULL };
		MonoObject* result = Mono::Instance().Invoke(AwardBlayfapItem, Store2_ClassInstance, args);

		if (bExtraDebug)
			LogInvoke("UnlockItems", "Result = " + (std::stringstream() << result).str());
	}

	HOOK_DEF(void, Store2_Update, (void* __this))
	{
		Store2_ClassInstance = __this;
		return oStore2_Update(__this);
	}

public:
	UnlockItems() {};

	void Render() override
	{
		if (ImGui::Button("Add Items"))
			Run();

		ImGui::SameLine();

		ImGui::Text("This does not work atm");
	}

	void Create() override
	{
		Store2_Update = Mono::Instance().GetCompiledMethod("Store2", "Update", 0);
		if (Store2_Update == nullptr)
		{
			LogHook(HookLogReason::Error, "Store2.Update", "Failed to get method pointer");
		}

		LogHook(HookLogReason::Create, "Store2.Update");
		CreateHook(Store2_Update);

		LogHook(HookLogReason::Enable, "Store2.Update");
		EnableHook(Store2_Update);
	}
		

	void Destroy() override
	{
		LogHook(HookLogReason::Destroy, "Store2.Update");
		DisableHook(Store2_Update);
	}
};