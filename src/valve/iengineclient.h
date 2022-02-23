#pragma once
#include "../util/memory.h"

class IEngineClient
{
public:
	constexpr std::int32_t GetLocalPlayerIndex() noexcept 
	{
		return memory::Call<std::int32_t>(this, 12);
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
