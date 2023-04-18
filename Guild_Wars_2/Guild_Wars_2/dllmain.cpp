#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

#include "GameData.h"
#include "../../MemLib/mem.h"


DWORD WINAPI HackThread(HMODULE hModule) {
	// Create console.

	// AllocConsole - Allocates new console for colling process.
	AllocConsole();
	FILE* fp = NULL;

	// Securely open file stream.
	freopen_s(&fp, "CONOUT$", "w", stdout);

	std::cout << "OG for a fee, stay sippin' fam\n";


	// Get module base.
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"Gw2-64.exe");

	PlayerBody* pPlayerBody = (PlayerBody*)mem::FindDMAAddy(moduleBase + 0x027D0130, { 0x50, 0x0 });
	
	// Hack loop.

	for (;;) {
		// Key input.

		if (!pPlayerBody)
		{
			break;
		}

		if (GetAsyncKeyState(VK_END) & 1) {
			break;
		}

		if (GetAsyncKeyState(VK_SPACE) & 1)
		{
			pPlayerBody->velocity.z += 10;
		}

		Sleep(5);
	}



	// Cleanup & Eject.
	fclose(fp);

	// FreeConsole - Detaches calling process from its console.
	FreeConsole();

	// FreeLibraryAndExitThread - Decrements the reference count of a loaded DLL and calls ExitThread.
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		/* CreateThread - Creates a thread and returns a HANDLE.
		*  CloseHandle - Cloases handle.
		*/
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

