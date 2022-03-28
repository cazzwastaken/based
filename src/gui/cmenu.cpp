#include "cmenu.hpp"

void CMenu::Setup(IDirect3DDevice9* device) noexcept
{
	if (!dxSetup)
	{
		ImGui::CreateContext();

		ImGui_ImplWin32_Init(FindWindowA("Valve001", nullptr));
		ImGui_ImplDX9_Init(device);

		// Here you can initialize
		// textures, fonts, etc...

		dxSetup = true;
	}
}

void CMenu::Render() noexcept
{
	// If the menu isn't open
	if (!IsOpen()) return;

	ImGui::SetNextWindowSize(ImVec2(370.f, 420.f));
	ImGui::Begin("based", &guiOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	{
		// I would make this const but I can't cuz reference :')
		static bool cazzAwesome = true;
		// This one I'll let you choose
		static float cazzDSize = 2;

		ImGui::Checkbox("cazz is fucking awesome", &cazzAwesome);
		ImGui::SliderFloat("cazz's d size", &cazzDSize, 2, 45);
	}
	ImGui::End();
}

void CMenu::Press() noexcept
{
	guiOpen = !guiOpen;
}

bool CMenu::IsOpen() noexcept
{
	return guiOpen;
}