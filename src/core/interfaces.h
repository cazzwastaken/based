#pragma once
#include "globals.h"

#include "../valve/ibaseclientdll.h"
#include "../valve/icliententitylist.h"
#include "../valve/iclientmodeshared.h"
#include "../valve/iengineclient.h"
#include "../valve/imaterialsystem.h"
#include "../valve/istudiorender.h"

// learn more about interfaces -> https://www.youtube.com/watch?v=C0wGdwnaArA
namespace interfaces
{
	// call once to capture all interface pointers
	void Setup() noexcept;

	// capture an individual interface by name & module
	template <typename Interface>
	Interface* Capture(const char* moduleName, const char* interfaceName) noexcept;

	// interface pointers
	inline IBaseClientDLL* client = nullptr;
	inline IClientEntityList* entityList = nullptr;
	inline IClientModeShared* clientMode = nullptr;
	inline IEngineClient* engine = nullptr;
	inline IMaterialSystem* materialSystem = nullptr;
	inline IStudioRender* studioRender = nullptr;

	// other
	inline void* keyValuesSystem = nullptr;
}
