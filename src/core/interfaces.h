#pragma once
#include "globals.h"

// interfaces
#include "../valve/ibaseclientdll.h"
#include "../valve/icliententitylist.h"
#include "../valve/iclientmodeshared.h"
#include "../valve/ienginetrace.h"
#include "../valve/iglobalvars.h"
#include "../valve/iglowmanager.h"
#include "../valve/imaterialsystem.h"
#include "../valve/istudiorender.h"
#include "../valve/ivengineclient.h"
#include "../valve/ivmodelinfo.h"

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
	inline IEngineTrace* engineTrace = nullptr;
	inline IGlobalVars* globals = nullptr;
	inline IGlowManager* glow = nullptr;
	inline IMaterialSystem* materialSystem = nullptr;
	inline IStudioRender* studioRender = nullptr;
	inline IVEngineClient* engine = nullptr;
	inline IVModelInfo* modelInfo = nullptr;

	// other
	inline void* keyValuesSystem = nullptr;
}
