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
	constexpr const char* GetModelName(const CModel* model) noexcept
	{
		return memory::Call<const char*>(this, 3, model);
	}

	constexpr CStudioHdr* GetStuioModel(const CModel* model) noexcept
	{
		return memory::Call<CStudioHdr*>(this, 32, model);
	}
};
