#include "interfaces.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void interfaces::Setup() noexcept
{
	// capture the interfaces
	client = Capture<IBaseClientDLL>("client.dll", "VClient018");
	entityList = Capture<IClientEntityList>("client.dll", "VClientEntityList003");
	clientMode = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<unsigned int**>(client))[10] + 5);
	engineTrace = Capture<IEngineTrace>("engine.dll", "EngineTraceClient004");
	globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(client))[11] + 10);
	glow = *reinterpret_cast<IGlowManager**>(memory::glowManager);
	materialSystem = Capture<IMaterialSystem>("materialsystem.dll", "VMaterialSystem080");
	studioRender = Capture<IStudioRender>("studiorender.dll", "VStudioRender026");
	engine = Capture<IVEngineClient>("engine.dll", "VEngineClient014");
	modelInfo = Capture<IVModelInfo>("engine.dll", "VModelInfoClient004");
	device = **reinterpret_cast<IDirect3DDevice9***>(memory::PatternScan("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 0x1);

	// get the exported KeyValuesSystem function
	if (const HINSTANCE handle = GetModuleHandle("vstdlib.dll"))
		// set our pointer by calling the function
		keyValuesSystem = reinterpret_cast<void* (__cdecl*)()>(GetProcAddress(handle, "KeyValuesSystem"))();
}

template <typename Interface>
Interface* interfaces::Capture(const char* moduleName, const char* interfaceName) noexcept
{
	const HINSTANCE handle = GetModuleHandle(moduleName);

	if (!handle)
		return nullptr;

	// get the exported Createinterface function
	using CreateInterfaceFn = Interface*(__cdecl*)(const char*, int*);
	const CreateInterfaceFn createInterface =
		reinterpret_cast<CreateInterfaceFn>(GetProcAddress(handle, "CreateInterface"));

	// return the interface pointer by calling the function
	return createInterface(interfaceName, nullptr);
}
