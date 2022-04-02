#pragma once
#include "../util/memory.h"

class IVPanel
{
public:
	constexpr const char* GetName(unsigned long panel) noexcept
	{
		return memory::Call<const char*>(this, 36, panel);
	}
};
