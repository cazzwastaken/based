#pragma once
#include "interfaces.h"

namespace hooks
{
	// call once to emplace all hooks
	void Setup() noexcept;

	// call once to restore all hooks
	void Destroy() noexcept;

	// bypass return address checks (thx osiris)
	using AllocKeyValuesMemoryFn = void* (__thiscall*)(void*, const std::int32_t) noexcept;
	inline AllocKeyValuesMemoryFn AllocKeyValuesMemoryOriginal;
	void* __stdcall AllocKeyValuesMemory(const std::int32_t size) noexcept;

	// example CreateMove hook
	using CreateMoveFn = bool(__thiscall*)(IClientModeShared*, float, CUserCmd*) noexcept;
	inline CreateMoveFn CreateMoveOriginal = nullptr;
	bool __stdcall CreateMove(float frameTime, CUserCmd* cmd) noexcept;
}
