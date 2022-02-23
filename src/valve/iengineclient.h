#pragma once
#include "../util/memory.h"

#include "cvector.h"
#include "iclientleafsystem.h"

class IEngineClient
{
public:
	// returns index of local player
	constexpr std::int32_t GetLocalPlayerIndex() noexcept 
	{
		return memory::Call<std::int32_t>(this, 12);
	}

	constexpr void SetViewAngles(const CVector& viewAngles) noexcept 
	{
		memory::Call<void, const CVector&>(this, 19, viewAngles);
	}

	// returns true if in-game
	constexpr bool IsInGame() noexcept 
	{
		return memory::Call<bool>(this, 26);
	}

	constexpr IClientLeafSystem* GetClientLeafSystem() noexcept 
	{
		return memory::Call<IClientLeafSystem*>(this, 43);
	}
};
