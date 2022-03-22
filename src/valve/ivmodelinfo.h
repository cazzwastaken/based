#pragma once
#include "../util/memory.h"

#include "cvector.h"

class CStudioHdr
{
public:

};

class CModel
{
public:
	std::int32_t handle;
	char name[260];
	std::int32_t loadFlags;
	std::int32_t serverCount;
	std::int32_t type;
	std::int32_t flags;
	CVector mins;
	CVector maxs;
	float radius;
};

class IVModelInfo
{
public:
	enum ERenderFlags : std::uint32_t
	{
		RENDER_FLAGS_DISABLE_RENDERING = 0x01,
		RENDER_FLAGS_HASCHANGED = 0x02,
		RENDER_FLAGS_ALTERNATE_SORTING = 0x04,
		RENDER_FLAGS_RENDER_WITH_VIEWMODELS = 0x08,
		RENDER_FLAGS_BLOAT_BOUNDS = 0x10,
		RENDER_FLAGS_BOUNDS_VALID = 0x20,
		RENDER_FLAGS_BOUNDS_ALWAYS_RECOMPUTE = 0x40,
		RENDER_FLAGS_IS_SPRITE = 0x80,
		RENDER_FLAGS_FORCE_OPAQUE_PASS = 0x100,
	};

	constexpr const char* GetModelName(const CModel* model) noexcept
	{
		return memory::Call<const char*>(this, 3, model);
	}

	constexpr CStudioHdr* GetStudioModel(const CModel* model) noexcept
	{
		return memory::Call<CStudioHdr*>(this, 32, model);
	}
};
