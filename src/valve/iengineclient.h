#pragma once
#include "../util/memory.h"

#include "cvector.h"

class IEngineClient
{
public:
	constexpr std::int32_t GetLocalPlayerIndex() noexcept 
	{
		return memory::Call<std::int32_t>(this, 12);
	}

	constexpr void SetViewAngles(const CVector& viewAngles) noexcept 
	{
		memory::Call<void, const CVector&>(this, 19, viewAngles);
	}

	constexpr bool InGame() noexcept 
	{
		return memory::Call<bool>(this, 26);
	}

	constexpr void* GetBSPQueryTree() noexcept 
	{
		return memory::Call<void*>(this, 43);
	}
};
