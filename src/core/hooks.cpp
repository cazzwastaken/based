#include "hooks.h"

// include minhook for epic hookage
#include "../../ext/minhook/minhook.h"
#include "../gui/cmenu.hpp"

#include <intrin.h>

// Instance our menu class, perhaps we could use smart pointers?
static CMenu menu;

void hooks::Setup() noexcept
{
	MH_Initialize();

	// AllocKeyValuesMemory hook
	MH_CreateHook(
		memory::Get(interfaces::keyValuesSystem, 1),
		&AllocKeyValuesMemory,
		reinterpret_cast<void**>(&AllocKeyValuesMemoryOriginal)
	);

	// CreateMove hook
	MH_CreateHook(
		memory::Get(interfaces::clientMode, 24),
		&CreateMove,
		reinterpret_cast<void**>(&CreateMoveOriginal)
	);

	// EndScene hook
	MH_CreateHook(
		memory::Get(interfaces::device, 42),
		&EndScene,
		reinterpret_cast<void**>(&EndSceneOriginal)
	);

	// Reset hook
	MH_CreateHook(
		memory::Get(interfaces::device, 16),
		&Reset,
		reinterpret_cast<void**>(&ResetOriginal)
	);

	MH_EnableHook(MH_ALL_HOOKS);
}

void hooks::Destroy() noexcept
{
	// restore hooks
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);

	// uninit minhook
	MH_Uninitialize();
}

void* __stdcall hooks::AllocKeyValuesMemory(const std::int32_t size) noexcept
{
	// if function is returning to speficied addresses, return nullptr to "bypass"
	if (const std::uint32_t address = reinterpret_cast<std::uint32_t>(_ReturnAddress());
		address == reinterpret_cast<std::uint32_t>(memory::allocKeyValuesEngine) ||
		address == reinterpret_cast<std::uint32_t>(memory::allocKeyValuesClient)) 
		return nullptr;

	// return original
	return AllocKeyValuesMemoryOriginal(interfaces::keyValuesSystem, size);
}

bool __stdcall hooks::CreateMove(float frameTime, CUserCmd* cmd) noexcept
{
	// make sure this function is being called from CInput::CreateMove
	if (!cmd->commandNumber)
		return CreateMoveOriginal(interfaces::clientMode, frameTime, cmd);

	// this would be done anyway by returning true
	if (CreateMoveOriginal(interfaces::clientMode, frameTime, cmd))
		interfaces::engine->SetViewAngles(cmd->viewAngles);

	// get our local player here
	globals::UpdateLocalPlayer();

	if (globals::localPlayer && globals::localPlayer->IsAlive())
	{
		// example bhop
		if (!(globals::localPlayer->GetFlags() & CEntity::FL_ONGROUND))
			cmd->buttons &= ~CUserCmd::IN_JUMP;
	}

	return false;
}

LONG __stdcall hooks::EndScene(IDirect3DDevice9* device) noexcept
{
	static const auto retAddr = _ReturnAddress();
	const auto result = EndSceneOriginal(device, device);

	if (_ReturnAddress() == retAddr)
		return result;

	// This prevents OBS from capturing our ESP/Menu, of course cazz you will not want to have this XD
	// You can change this in main.cpp or just click F12 and go to definition
#if CAZZ_BIG_MAN == FALSE
	static std::uintptr_t gameOverlayRetAddr = 0;

	if (!gameOverlayRetAddr)
	{
		MEMORY_BASIC_INFORMATION memInfo;
		VirtualQuery(_ReturnAddress(), &memInfo, sizeof(MEMORY_BASIC_INFORMATION));

		char fileName[MAX_PATH];
		GetModuleFileNameA(reinterpret_cast<HMODULE>(memInfo.AllocationBase), fileName, MAX_PATH);

		if (strstr(fileName, "gameoverlay"))
			gameOverlayRetAddr = reinterpret_cast<std::uintptr_t>(_ReturnAddress());
	}

	if (gameOverlayRetAddr != reinterpret_cast<std::uintptr_t>(_ReturnAddress()))
		return result;
#endif

	menu.Setup(device);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	// Exercise: Get Input class and disable game input when the menu is open :D
	menu.Render();

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}

WNDPROC oldWindow = reinterpret_cast<WNDPROC>(
	SetWindowLongPtr(FindWindowA("Valve001", nullptr), GWL_WNDPROC, reinterpret_cast<LONG_PTR>(hooks::WndProcess))
);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall hooks::WndProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(GUI_KEY) & 1)
		menu.Press();

	if (menu.IsOpen() && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return 1L;

	return CallWindowProc(oldWindow, hWnd, uMsg, wParam, lParam);
}