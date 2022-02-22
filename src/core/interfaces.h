#pragma once
#include "globals.h"

#include "../valve/ibaseclientdll.h"

namespace interfaces
{
	// call once to capture all interface pointers
	void Setup() noexcept;

	// capture an individual interface by name & module
	template <typename Interface>
	Interface* Capture(const char* moduleName, const char* interfaceName) noexcept;

	// interface pointers
	inline IBaseClientDLL* client = nullptr;
}
