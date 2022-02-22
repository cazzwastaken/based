#pragma once
#include "../util/memory.h"
#include "../core/netvars.h"

class CEntity
{
public:
	// example netvar
	NETVAR(GetFlags, "CBasePlayer->m_fFlags", std::uint32_t)

	// example virtual functions
	constexpr std::int32_t GetTeamNumber() noexcept 
	{
		return memory::Call<std::int32_t>(this, 88);
	}

	constexpr std::int32_t GetHealth() noexcept
	{
		return memory::Call<std::int32_t>(this, 122);
	}

	constexpr bool IsAlive() noexcept 
	{
		return memory::Call<bool>(this, 156);
	}

	constexpr bool IsPlayer() noexcept 
	{
		return memory::Call<bool>(this, 158);
	}
};
