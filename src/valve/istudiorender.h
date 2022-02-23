#pragma once
#include "../util/memory.h"

class CEntity;
class CDrawModelInfo
{
public:
	void* studio;
	void* hardwareData;
	std::int32_t unused;
	std::int32_t skin;
	std::int32_t body;
	std::int32_t hitboxSet;
	CEntity* renderable;
};

class CMaterial;
class IStudioRender
{
public:
	constexpr void ColorModulate(const float* color) noexcept
	{
		memory::Call<void>(this, 27, color);
	}

	constexpr void AlphaModulate(const float alpha) noexcept
	{
		memory::Call<void>(this, 28, alpha);
	}

	constexpr void ForcedMaterialOverride(CMaterial* material, const std::int32_t type = 0, std::int32_t index = -1) noexcept
	{
		memory::Call<void>(this, 33, material, type, index);
	}
};
