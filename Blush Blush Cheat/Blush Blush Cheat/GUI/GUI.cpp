#include "GUI.hpp"
#include "Custom.hpp"

void GUI::Render()
{
	if (bWatermark)
		showWatermark(bWatermarkFPS, "OmegaWare.xyz (Crush Crush)", ImVec4(255, 255, 255, 255), ImVec4(255, 255, 255, 0));
	
	if (!bMenuOpen)
		return;

	//ImGui::ShowStyleEditor();

	ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT));
	ImGui::Begin("OmegaWare.xyz (Crush Crush)", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse);

	//	ImGui::SetCursorPos(ImVec2(6, 20));
	ImGui::BeginChild("##Cheat", ImVec2(ImGui::GetContentRegionAvail().x / 3, ImGui::GetContentRegionAvail().y), true);
	{
		ImGui::Text("Cheat");
		
		if (ImGui::Button("Unload"))
			bExit = true;
		ImGui::SameLine();
		if (ImGui::Button(con.GetVisibility() ? "Hide Console" : "Show Console"))
			con.ToggleVisibility();
		ImGui::Checkbox("Extra Debug Info", &bExtraDebug);
		ImGui::Checkbox("Watermark", &bWatermark);
		if (bWatermark)
			ImGui::Checkbox("Watermark FPS", &bWatermarkFPS);
	}
	ImGui::EndChild();
	
	ImGui::SameLine();

	ImGui::BeginChild("##Phone", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true);
	{
		ImGui::Text("Phone");
	
		phoneUtils.Render();
	}
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("##Misc", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
	{
		ImGui::Text("Misc");

		gameState.Render();
		giveDiamonds.Render();
		guyUtils.Render();
		miscUnlockers.Render();
		jobs.Render();
	}
	ImGui::EndChild();

	ImGui::End();
}
