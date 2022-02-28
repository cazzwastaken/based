#pragma once
#include "../util/memory.h"
#include "../core/netvars.h"

#include "cclientclass.h"
#include "cvector.h"

class CEntity
{
public:
	enum EFlags : std::int32_t
	{
		FL_ONGROUND = (1 << 0),
		FL_DUCKING = (1 << 1),
		FL_ANIMDUCKING = (1 << 2),
		FL_WATERJUMP = (1 << 3),
		FL_ONTRAIN = (1 << 4),
		FL_INRAIN = (1 << 5),
		FL_FROZEN = (1 << 6),
		FL_ATCONTROLS = (1 << 7),
		FL_CLIENT = (1 << 8),
		FL_FAKECLIENT = (1 << 9),
		FL_INWATER = (1 << 10),
		FL_FLY = (1 << 11),
		FL_SWIM = (1 << 12),
		FL_CONVEYOR = (1 << 13),
		FL_NPC = (1 << 14),
		FL_GODMODE = (1 << 15),
		FL_NOTARGET = (1 << 16),
		FL_AIMTARGET = (1 << 17),
		FL_PARTIALGROUND = (1 << 18),
		FL_STATICPROP = (1 << 19),
		FL_GRAPHED = (1 << 20),
		FL_GRENADE = (1 << 21),
		FL_STEPMOVEMENT = (1 << 22),
		FL_DONTTOUCH = (1 << 23),
		FL_BASEVELOCITY = (1 << 24),
		FL_WORLDBRUSH = (1 << 25),
		FL_OBJECT = (1 << 26),
		FL_KILLME = (1 << 27),
		FL_ONFIRE = (1 << 28),
		FL_DISSOLVING = (1 << 29),
		FL_TRANSRAGDOLL = (1 << 30),
		FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
	};

	// example netvar
	NETVAR(GetFlags, "CBasePlayer->m_fFlags", std::int32_t);

	// networkable virtual functions
	constexpr CClientClass* GetClientClass() noexcept
	{
		return memory::Call<CClientClass*>(this + sizeof(std::uintptr_t) * 2, 2);
	}

	constexpr bool IsDormant() noexcept
	{
		return memory::Call<bool>(this + sizeof(std::uintptr_t) * 2, 9);
	}

	constexpr std::int32_t GetIndex() noexcept
	{
		return memory::Call<std::int32_t>(this + sizeof(std::uintptr_t) * 2, 10);
	}

	// entity virtual functions
	constexpr CVector& GetAbsOrigin() noexcept
	{
		return memory::Call<CVector&>(this, 10);
	}

	constexpr std::int32_t GetTeam() noexcept 
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
