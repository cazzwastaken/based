#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <thread>

// expose our cheat to main.cpp
#include "core/hooks.h"

// setup our cheat & unload it when exit key is pressed
DWORD WINAPI Setup(LPVOID lpParam)
{
	memory::Setup();		// find signatures
	interfaces::Setup();    // capture interfaces
	netvars::Setup();		// dump latest offsets
	hooks::Setup();			// place hooks

	// sleep our thread until unload key is pressed
	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	hooks::Destroy();		// restore hooks

	// unload library
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	// dll is being loaded
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		// disable thread notifications
		DisableThreadLibraryCalls(hinstDLL);

		// create our "Setup" thread
		const HANDLE hThread = CreateThread(
			nullptr,
			NULL,
			Setup,
			hinstDLL,
			NULL,
			nullptr
		);

		// free thread handle because we have no use for it
		if (hThread)
			CloseHandle(hThread);
	}

	// successful DLL_PROCESS_ATTACH
	return TRUE;
}
