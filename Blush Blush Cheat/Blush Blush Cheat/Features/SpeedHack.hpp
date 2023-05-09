#pragma once
#include "Feature.hpp"

// UnityEngine.Time
// Token: 0x060014E3 RID: 5347
// public static extern void set_timeScale(float value)
// UnityEngine.Time.set_timeScale(float value)

class SpeedHack : Feature
{
private:
	bool enabled = false;
	bool toggle = false;
	float _timeScale = 3.0f;

	void Toggle()
	{
		if (toggle && !enabled)
		{
			enabled = true;
			SetTimeScale(_timeScale);
		}

		if (!toggle && enabled)
		{
			enabled = false;
			SetTimeScale(1.0f);
		}
	}

	void SetTimeScale(float timeScale)
	{
		MonoMethod* set_timeScale = Mono::Instance().GetMethod("Time", "set_timeScale", 1, "UnityEngine", "UnityEngine");
		if (set_timeScale == nullptr)
		{
			LogError("Time.set_timeScale", "Failed to get method pointer");
			return;
		}

		void* args[1] = { &timeScale };
		MonoObject* result = Mono::Instance().Invoke(set_timeScale, nullptr, args);
		
		if (bExtraDebug)
			LogInvoke("UnityEngine.Time.set_timeScale", "Result = " + (std::stringstream() << result).str());
	}
	
public:
	SpeedHack() {}
	
	void Render() override
	{
		ImGui::BeginChild("##SpeedHack", ImVec2(ImGui::GetContentRegionAvail().x / 3, ImGui::GetContentRegionAvail().y), true);
		{
			ImGui::Text("Speed Hack (Time Scale Override)");
			ImGui::InputFloat("##Set Time Scale", &_timeScale, 0.1f, 1.0f, 1);
			if (_timeScale < 1.0f)
				_timeScale = 1.0f;
			else if (_timeScale > 100.0f)
				_timeScale = 100.0f;

			ImGui::Checkbox("Enable", &toggle);
		}
		ImGui::EndChild();
		
		Toggle();
	}

	void Create() override {}
	void Destroy() override {}
};