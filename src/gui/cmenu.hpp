#pragma once

#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui/imgui_impl_win32.h"
#include "../../ext/imgui/imgui_impl_dx9.h"

#include <Windows.h>
#include <cstdint>

inline constexpr std::uint8_t GUI_KEY = VK_INSERT;

class CMenu
{
public:
	void Setup(IDirect3DDevice9*) noexcept;
	void Render() noexcept;
	void Press() noexcept;
	bool IsOpen() noexcept;

private:
	bool guiOpen = false,
		dxSetup = false;
};